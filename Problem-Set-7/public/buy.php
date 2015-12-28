<?php
    // configuration
    require("../includes/config.php"); 
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // get cash balance and go to buy form
        $user = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        render("buy_form.php", ["title" => TITLE_BUY, "user" => $user, "selSymbol" => isset($_GET["symbol"]) ? $_GET["symbol"] : ""]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must enter a stock symbol to purchase.");
        }
        if (!preg_match("/^\d+$/", $_POST["buyshares"]) || $_POST["buyshares"] == 0)
        {
            apologize("Please enter a valid number of shares to purchase.");
        }
        // lookup the stock price
        $stock = lookup($_POST["symbol"]);
        $cost = $stock["price"] * $_POST["buyshares"];
        $user = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        if ($stock != false && $user !== false)
        {
            // does user have enough cash for purchase?
            if ($cost <= $user[0]["cash"])
            {
                // add shares to holdings
                query("INSERT INTO holdings (id, symbol, shares) VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?", 
                    $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["buyshares"], $_POST["buyshares"]);
                // deduct purchase price from cash
                query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
                
                // add to transaction history
                recordTransaction(TRANS_BUY, strtoupper($_POST["symbol"]), $_POST["buyshares"], $stock["price"], $cost);
                
                redirect("history.php");
            }
            else
            {
                apologize("You can afford to buy at most " . number_format(floor($user[0]["cash"] / $stock["price"])) . " full shares of " . strtoupper($_POST["symbol"]) . " at the current price of $" . number_format($stock["price"], 2) . "/share.");
            }
        }
        else
        {
            apologize("Unable to retrieve stock/cash values.");
        }
    }
?>

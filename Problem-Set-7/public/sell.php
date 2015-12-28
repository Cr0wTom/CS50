<?php

    // configuration
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // set up all portfolio data
        require("../includes/portfolio_data.php");
    
        // render portfolio
        render("sell_form.php", 
            [
                "title" => TITLE_SELL, 
                "user" => $user, 
                "positions" => $positions, 
                "totalStockValue" => $totalStockValue, 
                "totalPortfolioValue" => $totalPortfolioValue
            ]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    
        // validate submission
        if (empty($_POST["sellstock"]))
        {
            apologize("You must select a stock in order to sell it.");
        }
        
        // get the latest stock price
        $stock = lookup($_POST["sellstock"]);
        
        // get the user's holdings for that stock
        $holdings = query("SELECT shares FROM holdings WHERE id = ? and symbol = ?", $_SESSION["id"], $_POST["sellstock"]);
        
        if ($stock !== false && $holdings !== false)
        {
        
            // delete, or "sell" the stock
            query("DELETE FROM holdings WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["sellstock"]);
            
            // update cash balance
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $stock["price"] * $holdings[0]["shares"], $_SESSION["id"]);
            
            // add to transaction history
            recordTransaction(TRANS_SELL, strtoupper($_POST["sellstock"]), $holdings[0]["shares"], $stock["price"], $stock["price"] * $holdings[0]["shares"]);
        
        }
        else
        {
            apologize("Database Error: unable to get stock price/user's holdings.");
        }
        
        // redirect to history for transaction confirmation
        redirect("history.php");
    }
?>

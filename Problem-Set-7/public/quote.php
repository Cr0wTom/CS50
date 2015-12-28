<?php
    // configuration
    require("../includes/config.php"); 
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("quote_form.php", ["title" => TITLE_QUOTE]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must enter a valid stock symbol to receive a quote.");
        }
        // lookup the stock price
        $stock = lookup($_POST["symbol"]);
        if ($stock != false)
        {
            // display the quote
            render("quote.php", ["title" => TITLE_QUOTE, "stock" => $stock]);
        }
        else
        {
            apologize("Unable to look up quote for " . $_POST["symbol"] . ".");
        }
    }
?>

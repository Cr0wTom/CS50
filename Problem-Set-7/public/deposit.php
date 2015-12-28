<?php
    // configuration
    require("../includes/config.php"); 
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // get cash balance and go to deposit form
        $user = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        render("deposit_form.php", ["title" => TITLE_DEPOSIT, "user" => $user]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (!preg_match("/^\d+\.\d\d$/", $_POST["funds"]) || $_POST["funds"] <= 0)
        {
            apologize("Please enter a positive amount of funds to deposit in your account, including cents.");
        }
        // add funds to cash balance
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["funds"], $_SESSION["id"]);
        
        // add to transaction history
        recordTransaction(TRANS_DEPOSIT, null, null, null, $_POST["funds"]);
        
        redirect("history.php");
    }
?>

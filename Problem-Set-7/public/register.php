<?php
    // configuration
    require("../includes/config.php");
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php",["title" => "Register"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username to create an account.");   
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide a password for your account.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password before a new account can be created.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your password and confirmation do not match.");
        }
        // insert new user into database
        $result = 
            query(
                "INSERT 
                    INTO users 
                    (username, hash, cash) 
                    VALUES (?, ?, ?)", 
                    $_POST["username"], crypt($_POST["password"]), START_CASH
            );
        // log user in automatically if successful
        if ($result !== false)
        {
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            
            if ($rows !== false)
            {
                $_SESSION["id"] = $rows[0]["id"];
                // add initial deposit to transaction history
                if (START_CASH > 0)
                {
                    recordTransaction(TRANS_DEPOSIT, null, null, null, START_CASH);
                }
                // redirect to portfolio
                redirect("/");
            }
            else
            {
                apologize("Unable to log in with new account.");
            }
        }
        // if database error occurred, alert user
        else
        {
            apologize("Database error - account not created.");
        }
    }
?>

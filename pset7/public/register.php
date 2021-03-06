<?php

    // confirmation
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // User input for the registration form, verify password & confirmation match
        if(empty($_POST["username"]))
        {
            apologize("You must enter a username.");
        }
        else if(empty($_POST["password"]))
        {
            apologize("You must enter a password.");
        }
        else if($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your password and confirmation do not match");
        }
        // perform query on user name, if match found return error, else add user to database
        else
        {
            // query users, and isert new user
            if(query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], crypt($_POST["password"])) === false)
            {
                apologize("Username already exists.");
            }
            else
            {
                //register
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;
                
                
                // Log the history
                $tran_date = date("Y-m-d H:i:s");
                $new_surrogate = $_SESSION["id"] . $tran_date . "DEPOSIT";           
                $transaction_history = query("INSERT INTO user_history (surrogate_id, user_id, transaction_date, name, credit, transaction_type) VALUES (?, ?, ?, ?, ?, ?)", 
                                        $new_surrogate, $_SESSION["id"], $tran_date, "DEPOSIT", 10000.00, 'PROMO');
                
                redirect("index.php");
            }
        }
        
    }    
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
?>

<?php

    // confirmation
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // User input for the registration form, verify password & confirmation match
        if(empty($_POST["username"]))
        {
            apologize("Username is required.");
        }
        else if(empty($_POST["password"]))
        {
            apologize("Password is required.");
        }
        else if($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Password and Confirmation do not match");
        }
        // perform query on user name, if match found return error, else add user to database
        else
        {
            // query users, and isert new user
            if(query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], crypt($_ST["password"])) === false)
            {
                apologize("Username already exists.");
            }
            else
            {
                //register
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;
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
<?php

    // configuration
    require("../includes/config.php");
    
    // if form is submitted by user
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate user input
        if(empty($_POST["stock"]))
        {
            apologize("Unable to complete request - please input a stock symbol, and try again.");
        }
        // validate units to sell
        if(empty($_POST["shares"]) || !is_numeric($_POST["shares"]) || !preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Unable to complete request - please verify units to sell, and try again.")
        }
        
        // query stock info from Yahoo, and validate user input
        $stock = lookup($_POST["stock"]);
        if ($stock === false)
        {
            apologize("Unable to complete request - please verify stock symbol, and try agai.") 
        }
        else
        {
            // calculate 
            
            // perform query on users portfolio to verify user input matches user portfolio
            if(!$shares = query("SELECT shares FROM user_portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]));
            {
                apologize("Unable to complete request - please verify stock symbol, and try again.");
            }
            else
            {
                
            }   
        }
        
    }
?>

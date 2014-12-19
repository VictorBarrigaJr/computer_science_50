<?php

    // configuration
    require("../includes/config.php");
    
    // if sell order form is submitted by user
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate user stock symbol input
        if(empty($_POST["stock"]))
        {
            apologize("Unable to complete request - please input a stock symbol, and try again.");
        }
        
        // validate user units to sell input
        if(empty($_POST["units"]) || !is_numeric($_POST["units"]) || $_POST["units"] <= 0)
        {
            apologize("Unable to complete request - please input the total units to sell, and try again.");
        }
        
        // query and validate the user request is in portfolio by stock and shares are correct 
        $rows = query(  "SELECT shares FROM user_portfolios WHERE user_id = ? and symbol = ?", $_SESSION["id"], strtoupper($_POST["stock"]));
        if (count($rows) == 1)
        {
            $user_shares = $rows[0]["shares"];
        }
        else
        {
            apologize("Unable to complete request - please verify stock is currently in portfolio.");
        }
        
        if ($_POST["units"] > $user_shares)
        {
             apologize("Unable to complete request - please verify the total units to sell, and try again.");        
        }
       
        // query data from Yahoo, and validate user input
        $stock_sell = lookup($_POST["stock"]);
        // assigns the total sale value of sale request
        $value = $stock_sell["price"] * $_POST["units"];
        if ($stock_sell === false)
        {
            apologize("Unable to complete request - please verify stock symbol, and try again.");
        }
        else
        {
            // if request sells all units
            if($_POST["units"] == $user_shares)
            {            
                // Delete the user stocks
                $portfolio_update = query("DELETE FROM user_portfolios WHERE user_id = ? and symbol = ?", $_SESSION["id"], strtoupper($_POST["stock"]));
                
                if ($portfolio_update === false)
                {
                    apologize("Error while selling shares.");
                }
            }
            // update portfolio
            else
            {
                $new_shares = $user_shares - $_POST["units"];
                
                // update shares
                $portfolio_update = query("UPDATE user_portfolios SET shares = ? WHERE user_id = ? and symbol = ?", $new_shares, $_SESSION["id"], strtoupper($_POST["stock"]));
                if ($portfolio_update === false)
                {
                    apologize("Error while selling shares.");
                }
            }
            
            // Update users cash
            $cash_update = query("UPDATE users SET cash = cash + ? where id = ?", $value, $_SESSION["id"]);
            if ($cash_update === false)
            {
               apologize("Error while selling shares.");
            }
               
            //$_SESSION["cash"] += $value;
            
            // Log the history
            /*$query = query("INSERT INTO history(user_id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, Now())"
                ,$_SESSION["id"], 0, strtoupper($_POST["code"]), $shares, $stock["price"]);
            */
            
            // Redirect to home
            render("../templates/sell_info_form.php", ["title" => "Sell", "stock_sell" => $stock_sell, "value" => $value]);        
        }
    }
    // form has not been submitted
    else
    {
        render("sell_form.php", ["title" => "Sell"]);
    }
    ?>

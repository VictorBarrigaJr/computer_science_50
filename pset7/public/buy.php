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
        // validate units to sell preg_match("/^\d+$/", $_POST["shares"])
        if(empty($_POST["shares"]) || !is_numeric($_POST["shares"]) || !preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Unable to complete request - please verify shares to buy, and try again.");
        }
        // validate users cash
        $current_cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        // query stock info from Yahoo, and validate user input
        //$temp = strtoupper($_POST["stock"])
        $stock_buy = lookup(strtoupper($_POST["stock"]));
        $value = $stock_buy["price"] * $_POST["shares"];
        if ($stock_buy === false )
        {
            apologize("Unable to complete request - please verify stock symbol, and try again.");
        }
        // check if user has sufficient funds
        else if ($current_cash < $value)
        {
            apologize("Unable to complete request - insufficent funds.");
        }
        // update users portfolio and cash
        else
        {
            $new_surrogate = $_SESSION['id'] . $stock_buy["symbol"];
            // Insert the bought stock into database
            $update_portfolio = query("INSERT INTO user_portfolios (user_id, symbol, shares, surrogate_id) VALUES (?, ?, ?, ?)
                                        ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", 
                                        $_SESSION["id"], $stock_buy["symbol"], $_POST["shares"], $new_surrogate);
            if ($update_portfolio === false)
            {
            apologize("Error while buying shares.");
            }
            
            // Update the user's cash
            $update_cash = query("UPDATE users SET cash = cash - ? where id = ?", $value, $_SESSION["id"]);
            if ($update_cash === false)
            {
                apologize("Error while buying shares.");
            }      
            // Log the history
            $tran_date = date("Y-m-d H:i:s");
            $new_surrogate = $_SESSION["id"] . $tran_date . $stock_buy["symbol"];
            //$money = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);          
            $transaction_history = query("INSERT INTO user_history (surrogate_id, user_id, transaction_date, name, symbol, shares, credit, debit, transaction_type, fill_price) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", 
                                        $new_surrogate, $_SESSION["id"], $tran_date, $stock_buy["name"], $stock_buy["symbol"], $_POST["shares"], 0, $value, 'BUY', $stock_buy["price"]);
            // Redirect to home
            render("../templates/buy_form_info.php", ["title" => "Buy", "stock_buy" => $stock_buy, "value" => $value]);  
        }         
    }
    else
    {
        // render form
        render("buy_form.php", ["title" => "Buy"]);
    }
?>

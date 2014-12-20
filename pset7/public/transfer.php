<?php

    // confirmation
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
       // validate amount
       if(empty($_POST["amount"]) || !is_numeric($_POST["amount"]) || !preg_match("/^\d+$/", $_POST["amount"]))
       {
            apologize("Unable to complete request - please verify amount and try again.");           
       }
       if((($_POST["from_account"] == "C$50_Finance_Account") && ($_POST["to_account"] == "C$50_Finance_Account")) || 
           (($_POST["from_account"] == "Checking_Account") && ($_POST["to_account"] == "Checking_Account")))
       {
           apologize("Unable to complete request - please verify accounts and try again."); 
       }
       // if transfer from_account is C$50 query and validate funds Withdrawl
       if($_POST["from_account"] == "C$50_Finance_Account")
       {
            // if users balance is equal or greater than amount transfer
            if($_POST["amount"] <= ($current_cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"])))
            {
                // Update users cash
                $cash_update = query("UPDATE users SET cash = cash - ? where id = ?", $_POST["amount"], $_SESSION["id"]);
                if ($cash_update === false)
                {
                    apologize("Error while selling shares.");
                }
                
                // Log the history
                $tran_date = date("Y-m-d H:i:s");
                $new_surrogate = $_SESSION["id"] . $tran_date . "WITHDRAWAL";           
                $transaction_history = query("INSERT INTO user_history (surrogate_id, user_id, transaction_date, name, debit, transaction_type) VALUES (?, ?, ?, ?, ?, ?)", 
                                        $new_surrogate, $_SESSION["id"], $tran_date, "TRANSFER", $_POST["amount"], 'WITHDRAWAL');
                
                // Redirect to confirmation
                render("../templates/transfer_form_info.php", ["title" => "Transfer"]);
   
            }
            else
            {
                apologize("Unable to complete request - insufficent funds.");
            }
       }
       // deposit into C$50
       else
       {
            // Update users cash
            $cash_update = query("UPDATE users SET cash = cash + ? where id = ?", $_POST["amount"], $_SESSION["id"]);
            if ($cash_update === false)
            {
                apologize("Error while selling shares.");
            }
            
            // Log the history
            $tran_date = date("Y-m-d H:i:s");
            $new_surrogate = $_SESSION["id"] . $tran_date . "DEPOSIT";           
            $transaction_history = query("INSERT INTO user_history (surrogate_id, user_id, transaction_date, name, credit, transaction_type) VALUES (?, ?, ?, ?, ?, ?)", 
                                    $new_surrogate, $_SESSION["id"], $tran_date, "TRANSFER", $_POST["amount"], 'DEPOSIT');
        
            // Redirect to confirmation
            render("../templates/transfer_form_info.php", ["title" => "Transfer"]);
   
       }               
    }    
    else
    {
        // else render form
        render("transfer_form.php", ["title" => "Transfer"]);
    }
    
?>

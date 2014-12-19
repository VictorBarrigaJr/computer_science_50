<?php
    // configuration
    require("../includes/config.php");  
    
    // query cash for template
    $cash =	query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);	
    
	// create new array to store all info for history table
    $transaction_history = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    
    // render sell form
    render("history_form.php", ["title" => "Transaction History", "cash" => $cash, "transaction_history" => $transaction_history]);
   
?>

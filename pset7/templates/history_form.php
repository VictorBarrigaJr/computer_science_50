<div>
    <ul class="nav nav-pills">
        <li><a href="index.php">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>

<!-- table to display user portfolio --> 
<table class="table table-striped">
     <caption>Transaction History</caption>
     <thead>
        <tr>
            <th>Date</th>
            <th>Transaction Type</th>
            <th>Transaction Information</th>
            <th>Shares</th>
            <th>Fill Price</th>
            <th>Credit</th>
            <th>Debit</th>
        </tr>
    </thead>
    
    <tbody>
        <?php
                      
            foreach ($transaction_history as $row)
            {
                echo("<tr>");
                    echo("<td>" . date('d/m/y g:i A', strtotime($row[transaction_date])) . "</td>");
                    echo("<td>" . $row("transaction_type") . "</td>");
                    echo("<td>" . $row["name"] . . " " . "(" . $row["symbol"] . ")" . "</td>");
                    echo("<td>" . $row["shares"] . "</td>");
                    echo("<td>" . "$" . number_format($row["fill_price"], 2) . "</td>");
                    echo("<td>" . "$" . number_format($row["credit"], 2) . "</td>");
                    echo("<td>" . "$" . number_format($row["debit"], 2) . "</td>");
                echo("</tr>");
            }
        ?>
    </tbody>
</table>

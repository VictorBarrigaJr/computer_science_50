<!-- table to display user portfolio --> 
<table class="table table-striped">
     <caption>
        <h1>
            Transaction History
        </h1>
     </caption>
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
                    echo("<td>" . $row["transaction_date"] . "</td>");
                    echo("<td>" . $row["transaction_type"] . "</td>");
                    echo("<td>" . $row["name"] . " " . "(" . $row["symbol"] . ")" . "</td>");
                    echo("<td>" . $row["shares"] . "</td>");
                    echo("<td>" . "$" . number_format($row["fill_price"], 2) . "</td>");
                    echo("<td>" . "$" . number_format($row["credit"], 2) . "</td>");
                    echo("<td>" . "$" . number_format($row["debit"],2)  . "</td>");
                echo("</tr>");
            }
        ?>
    </tbody>
</table>

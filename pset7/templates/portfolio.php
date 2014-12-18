<!-- table to display user portfolio --> 
<table class="table table-striped">
     <caption>Portfolio</caption>
     <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
    </thead>
    
    <tbody>
        <?php
                      
            foreach ($portfolio as $row)
            {
                echo("<tr>");
                    echo("<td>" . $row["symbol"] . "</td>");
                    echo("<td>" . $row["name"] . "</td>");
                    echo("<td>" . $row["shares"] . "</td>");
                    echo("<td>" . "$" . number_format($row["price"], 2) . "</td>");
                    echo("<td>" . "$" . number_format($row["total"], 2) . "</td>");
                echo("</tr>");
            }
        ?>
        
        <tr>
            <td colspan="4">CASH</td>      
            <td>$<?=number_format($users[0]["cash"], 2)?></td>
        </tr>
    </tbody>
</table>

<div>
    <a href="logout.php">Log Out</a>
</div>

<div>
    <ul class="nav nav-pills">
        <li><a href="index.php">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>

<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="stock" placeholder="Stock" type="text"/>
        </div>
        <div class="form-group">
            <input autofocus class="form-control" name="units" placeholder="Units" type="text"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>

<div>
    Current Cash Balance:&nbsp;&nbsp;<b><?= "$" . number_format($user[0]["cash"], 2) ?></b><br/>
    <br/>

    <form action="buy.php" method="post">
        <fieldset>
            <div class="form-group">
                <input <?php print(empty($selSymbol) ? "autofocus" : "") ?> class="form-control" name="symbol" placeholder="Stock Symbol" type="text" value="<?= $selSymbol ?>"/>
            </div>
            <div class="form-group">
                <input autofocus class="form-control" name="buyshares" placeholder="Shares to Buy" type="text"/>
            </div>
            <div class="form-group">
                <button type="submit" class="btn btn-default">Buy</button>
            </div>
        </fieldset>
    </form>
</div>

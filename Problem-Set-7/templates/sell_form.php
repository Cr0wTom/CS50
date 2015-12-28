<div>
    <?php if (!empty($positions)): ?>
        <form action="sell.php" method="post">
            <table class="table table-striped cs50">
                <thead>
                    <tr>
                        <td style="text-align: center;"><b>Select</b></td>
                        <td style="text-align: left;"><b>Name</b></td>
                        <td style="text-align: left;"><b>Symbol</b></td>
                        <td style="text-align: right;"><b>Shares</b></td>
                        <td style="text-align: right;"><b>Price</b></td>
                        <td style="text-align: right;"><b>Value</b></td>
                    </tr>
                </thead>

                <tbody>
                    <?php foreach ($positions as $position): ?>
                        <tr>
                            <td style="text-align: center;"><input type="radio" name="sellstock" value="<?= $position["symbol"] ?>" <?php print($position["symbol"] == $positions[0]["symbol"] ? "checked" : ""); ?>/></td>
                            <td style="text-align: left;"><?= $position["name"] ?></td>
                            <td style="text-align: left;"><?= $position["symbol"] ?></td>
                            <td style="text-align: right;"><?= number_format($position["shares"]) ?></td>
                            <td style="text-align: right;"><?= "$" . number_format($position["price"], 2) ?></td>
                            <td style="text-align: right;"><?= "$" . number_format($position["value"], 2) ?></td>
                        </tr>
                    <?php endforeach ?>
                </tbody>
            </table>

            <div class="form-group">
                <button type="submit" class="btn btn-default">Sell Selected Stock</button>
            </div>
        </form>
    <?php else: ?>
        Np stock for shell.  <a href="buy.php">Would you like to buy stock?</a>
    <?php endif ?>
</div>

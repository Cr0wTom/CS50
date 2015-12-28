<div>
    <table class="table table-striped cs50">
        <thead>
            <tr>
                <td style="text-align: left;"><b>Name</b></td>
                <td style="text-align: left;"><b>Symbol</b></td>
                <td style="text-align: right;"><b>Shares</b></td>
                <td style="text-align: right;"><b>Price</b></td>
                <td style="text-align: right;"><b>Value</b></td>
            </tr>
        </thead>
        
        <tbody>
            <?php if (!empty($positions)): ?>
                <?php foreach ($positions as $position): ?>
                    <tr>
                        <td style="text-align: left;"><?= $position["name"] ?></td>
                        <td style="text-align: left;"><?= $position["symbol"] ?></td>
                        <td style="text-align: right;"><?= number_format($position["shares"]) ?></td>
                        <td style="text-align: right;"><?= "$" . number_format($position["price"], 2) ?></td>
                        <td style="text-align: right;"><?= "$" . number_format($position["value"], 2) ?></td>
                    </tr>
                <?php endforeach ?>
            <?php else: ?>
                <tr>
                    <td colspan="5" style="text-align: left;">(No stocks in portfolio)</td>
                </tr>
            <?php endif ?>

            <tr style="text-align: right;">
                <td colspan="4"><b>Total Stock:</b></td>
                <td><?= "$" . number_format($totalStockValue, 2) ?></td>
            </tr>
            <tr style="text-align: right;">
                <td colspan="4"><b>Total Cash:</b></td>
                <td><?= "$" . number_format($user[0]["cash"], 2) ?></td>
            </tr>
            <tr style="text-align: right;">
                <td colspan="4"><b>Total Portfolio:</b></td>
                <td><?= "$" . number_format($totalPortfolioValue, 2) ?></td>
            </tr>
        </tbody>
    </table>
</div>

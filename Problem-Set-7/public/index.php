<?php

    // configuration
    require("../includes/config.php"); 
    
    // query databases
    $user = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $holdings = query("SELECT symbol, shares FROM holdings WHERE id = ? ORDER BY symbol", $_SESSION["id"]);
        
    $positions = [];
    $totalStockValue = 0;
    
     // determine position on each holding
    foreach ($holdings as $holding)
    {
        $stock = lookup($holding["symbol"]);
        
        if ($stock !== false)
        {
            $positions[] = [
                "name"   => $stock["name"],
                "symbol" => $stock["symbol"],
                "shares" => $holding["shares"],
                "price"  => $stock["price"],
                "value"  => $stock["price"] * $holding["shares"]
            ];
            
            // grand total of all stocks held
            $totalStockValue += $stock["price"] * $holding["shares"];
        }
    }
    
    $totalPortfolioValue = $totalStockValue + $user[0]["cash"];
    
?>

module("Stock", package.seeall)

local oo = require("OOHelper");

Stock = {}

Stock.stockCounter = 0;

function Stock.new()
    local obj = {
        market = 0,
        code = 0,
        name = "",
        price = 0,
        openPrice = 0,
        
        className = "Stock",
    }
    
    Stock.stockCounter = Stock.stockCounter + 1;
    
    obj = oo.newObject(obj, Stock)

    return obj
end

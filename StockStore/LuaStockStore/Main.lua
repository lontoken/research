module("Main", package.seeall)

local stock = require("Stock");
local stockTreeNote = require("StockTreeNote");
local stockTree = require("StockTree");

local function testAdd(root)
    for code = 300000, 302000 do
        root:AddStock(code);
    end
    
    for code = 400000, 402000 do
        root:AddStock(code);
    end
    
    for code = 600000, 406000 do
        root:AddStock(code);
    end
end


local function testGet(root)
    for code = 300000, 302000 do
        root:GetStock(code);
    end
    
    for code = 400000, 402000 do
        root:GetStock(code);
    end
    
    for code = 600000, 406000 do
        root:GetStock(code);
    end
end


local function main()
    local root = stockTree.StockTree.new()
    print("start");
    
    print("add start. " .. os.clock());
    testAdd(root);
    
    print("add end. " .. os.clock());
    
    testGet(root);
    
    print("get end. " .. os.clock());
    
    print("end. note: " .. stockTreeNote.StockTreeNote.noteCounter .. ", stock: " .. stock.Stock.stockCounter
            .. ", search: " .. stockTreeNote.StockTreeNote.searchCounter);
end

main();
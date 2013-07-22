module("StockTree", package.seeall)

local stock = require("Stock");
local oo = require("OOHelper");
local note = require("StockTreeNote");

StockTree = {}

function StockTree.new()
    local obj = {
        root = {},
        className = "StockTree",
    }
    
    obj.root = note.StockTreeNote.new();
    
    obj = oo.newObject(obj, StockTree);

    return obj
end


function StockTree:AddStock(stk)
    if type(stk) == "number" then
        local data = self.root:AddNumCode(stk);
        data.code = stk;
    elseif type(stk) == "string" then
        local code = tonumber(stk);
        local data = self.root:AddNumCode(code);
        data.code = code;
    elseif type(stk) == "table" then
        local data = self.root:AddNumCode(stk.code);
        data.code = stk.code;
    end
end


function StockTree:GetStock(stk)
    if type(stk) == "number" then
        local data = self.root:GetNumCode(stk);
        return data;
    elseif type(stk) == "string" then
        local code = tonumber(stk);
        local data = self.root:GetNumCode(code);
        return data;
    end
end
module("StockTreeNote", package.seeall)

local stock = require("Stock");
local oo = require("OOHelper");

StockTreeNote = {}

StockTreeNote.noteCounter = 0;
StockTreeNote.searchCounter = 0;

function StockTreeNote.new()
    local obj = {
        lever = 0,
        num = 0,
        list = {},
        data = {},
        
        className = "StockTreeNote",
    }
    
    obj.list = {[0] = {}, [1] = {}, [2] = {}, [3] = {}, [4] = {}, [5] = {}, [6] = {}, [7] = {}, [8] = {}, [9] = {}};
    
    StockTreeNote.noteCounter = StockTreeNote.noteCounter + 1;
        
    obj.data = stock.Stock.new();
    
    obj = oo.newObject(obj, StockTreeNote)

    return obj
end

local function GenerateCodeNums(num, out)
    local tNum = num;
    out.bit_1 = tNum / 100000;
    tNum = tNum % 100000;

    out.bit_2 = tNum / 10000;
    tNum = tNum % 10000;

    out.bit_3 = tNum / 1000;
    tNum = tNum % 1000;

    out.bit_4 = tNum / 100;
    tNum = tNum % 100;

    out.bit_5 = tNum / 10;
    tNum = tNum % 10;

    out.bit_6 = tNum / 1;
    
    return true;
end


function StockTreeNote:AddNumCode(code)
    local bits = {bit_1 = 0, bit_2 = 0, bit_3 = 0, bit_4 = 0, bit_5 = 0, bit_6 = 0,};
    GenerateCodeNums(code, bits);
    
    local cur = self;
    
    if (type(cur.list[bits.bit_1]) ~= "table") or (cur.list[bits.bit_1].class ~= "StockTreeNote") then
        cur.list[bits.bit_1] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_1];
    
    if (type(cur.list[bits.bit_2]) ~= "table") or (cur.list[bits.bit_2].class ~= "StockTreeNote") then
        cur.list[bits.bit_2] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_2];
    
    if (type(cur.list[bits.bit_3]) ~= "table") or (cur.list[bits.bit_3].class ~= "StockTreeNote") then
        cur.list[bits.bit_3] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_3];
    
    if (type(cur.list[bits.bit_4]) ~= "table") or (cur.list[bits.bit_4].class ~= "StockTreeNote") then
        cur.list[bits.bit_4] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_4];
    
    if (type(cur.list[bits.bit_5]) ~= "table") or (cur.list[bits.bit_5].class ~= "StockTreeNote") then
        cur.list[bits.bit_5] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_5];
    
    if (type(cur.list[bits.bit_6]) ~= "table") or (cur.list[bits.bit_6].class ~= "StockTreeNote") then
        cur.list[bits.bit_6] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_6];
    
    return cur.data;
end


function StockTreeNote:GetNumCode(code)
    local bits = {bit_1 = 0, bit_2 = 0, bit_3 = 0, bit_4 = 0, bit_5 = 0, bit_6 = 0,};
    GenerateCodeNums(code, bits);
    
    local cur = self;
    
    if (type(cur.list[bits.bit_1]) ~= "table") or (cur.list[bits.bit_1].class ~= "StockTreeNote") then
        cur.list[bits.bit_1] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_1];
    
    if (type(cur.list[bits.bit_2]) ~= "table") or (cur.list[bits.bit_2].class ~= "StockTreeNote") then
        cur.list[bits.bit_2] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_2];
    
    if (type(cur.list[bits.bit_3]) ~= "table") or (cur.list[bits.bit_3].class ~= "StockTreeNote") then
        cur.list[bits.bit_3] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_3];
    
    if (type(cur.list[bits.bit_4]) ~= "table") or (cur.list[bits.bit_4].class ~= "StockTreeNote") then
        cur.list[bits.bit_4] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_4];
    
    if (type(cur.list[bits.bit_5]) ~= "table") or (cur.list[bits.bit_5].class ~= "StockTreeNote") then
        cur.list[bits.bit_5] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_5];
    
    if (type(cur.list[bits.bit_6]) ~= "table") or (cur.list[bits.bit_6].class ~= "StockTreeNote") then
        cur.list[bits.bit_6] = StockTreeNote.new();
    end
    cur = cur.list[bits.bit_6];
    
    StockTreeNote.searchCounter = StockTreeNote.searchCounter + 1;
    
    return cur.data;
end
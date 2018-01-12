module(...,package.seeall)

local UART_ID = 1

local CMD_SCANNER,CMD_GPIO,CMD_PORT,FRM_TAIL = 1,2,3,string.char(0xC0)

local rdbuf = ""

local function print(...)
	_G.print("test",...)
end

local function parse(data)
	if not data then return end	
	
	local tail = string.find(data,string.char(0xC0))
	if not tail then return false,data end	
	local cmdtyp = string.byte(data,1)
	local body,result = string.sub(data,2,tail-1)
	
	print("parse",common.binstohexs(data),cmdtyp,common.binstohexs(body))
	
	if cmdtyp == CMD_SCANNER then
		pio.pin.setlow(pio.P0_6)
		write("dioda on")
	elseif cmdtyp == CMD_GPIO then
		pio.pin.sethigh(pio.P0_6)
		write("dioda off")
	elseif cmdtyp == CMD_PORT then
		write("CMD_PORT")
	else
		write("CMD_ERROR")
	end
	
	return true,string.sub(data,tail+1,-1)	
end

local function proc(data)
	if not data or string.len(data) == 0 then return end

	rdbuf = rdbuf..data	
	
	local result,unproc
	unproc = rdbuf

	while true do
		result,unproc = parse(unproc)
		if not unproc or unproc == "" or not result then
			break
		end
	end

	rdbuf = unproc or ""
end

local function read()
	local data = ""

	while true do		
		data = uart.read(UART_ID,"*l",0)
		if not data or string.len(data) == 0 then break end

		proc(data)
	end
end

function write(s)
	print("write",s)
	uart.write(UART_ID,s.."\r\n")
end

pm.wake("test")

pio.pin.setdir(pio.OUTPUT, pio.P0_6)
pio.pin.setval(0, pio.P0_6)

sys.reguart(UART_ID,read)

uart.setup(UART_ID,115200,8,uart.PAR_NONE,uart.STOP_1)




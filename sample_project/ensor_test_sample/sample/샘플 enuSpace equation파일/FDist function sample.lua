function MathEquation()
local ensor_x = ensor.new("{#@ensor.FDist[:]}")
local ensor_y = ensor.FDist(ensor_x,6,4,false)
local ensor_y2 = ensor.FDist(ensor_x,6,4,true)

ensor.Plot(ensor_x, ensor_y)
ensor.Plot(ensor_x, ensor_y2)
ensor.Table(ensor_y)
ensor.Table(ensor_y2)
end
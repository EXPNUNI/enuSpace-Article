function MathEquation()
local ensor_x = ensor.new("{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}")
local ensor_y = ensor.PoissonDist(ensor_x,10,false)
local ensor_y2 = ensor.PoissonDist(ensor_x,10,true)

ensor.Plot(ensor_x, ensor_y)
ensor.Plot(ensor_x, ensor_y2)
ensor.Table(ensor_y)
ensor.Table(ensor_y2)
end
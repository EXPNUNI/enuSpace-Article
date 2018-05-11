function MathEquation()
local ensor_x = ensor.new("{#@ensor.PoissonDist[:]}")
local ensor_y = ensor.PoissonDist(ensor_x,10,false)
local ensor_y2 = ensor.PoissonDist(ensor_x,10,true)

ensor.Plot(ensor_x, ensor_y)
ensor.Plot(ensor_x, ensor_y2)
ensor.Table(ensor_y)
ensor.Table(ensor_y2)
end
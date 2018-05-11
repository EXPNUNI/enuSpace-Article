function MathEquation()
    local ensor_x = ensor.new("{#@ensor.ChisqDist[:]}")
    local ensor_y = ensor.ChisqDist(ensor_x,3,false)
    local ensor_y1 = ensor.ChisqDist(ensor_x,3,true)

    ensor.Table(ensor_y)
    ensor.Table(ensor_y1)
end
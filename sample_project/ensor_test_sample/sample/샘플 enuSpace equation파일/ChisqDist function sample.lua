function MathEquation()
    local ensor_x = ensor.new("{0.5,1,1.5,2,2.5,3,3.5,4,4.5,5}")
    local ensor_y = ensor.ChisqDist(ensor_x,3,false)
    local ensor_y1 = ensor.ChisqDist(ensor_x,3,true)

    ensor.Table(ensor_y)
    ensor.Table(ensor_y1)
end
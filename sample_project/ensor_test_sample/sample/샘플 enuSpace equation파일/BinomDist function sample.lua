function MathEquation()
     local ensor_x = ensor.new("{#@ensor.BinomDist[:]}")
     local ensor_y = ensor.BinomDist(ensor_x,10,0.5,false)
     local ensor_y2 = ensor.BinomDist(ensor_x,10,0.5,true)

     ensor.Plot(ensor_x, ensor_y)
     ensor.Plot(ensor_x, ensor_y2)
     ensor.Table(ensor_y)
     ensor.Table(ensor_y2)
end
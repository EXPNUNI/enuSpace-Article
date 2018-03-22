
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      SUBROUTINE MAIN_PROC()

      USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT !.. Add other objects as needed
      USE Interface_to_C_Func

      REAL*8 DATA_VALUE 
      REAL*8 ARRAY_VALUE(3,3)
      
      DATA_VALUE = GetValue('@CORE.flux00')
      DATA_VALUE = DATA_VALUE + 0.1
      CALL SetValue('@CORE.flux00', DATA_VALUE)

  
      ARRAY_VALUE(1,1) = GetArrayValue('@CORE.flux[0][0]')
      ARRAY_VALUE(2,1) = GetArrayValue('@CORE.flux[0][1]]')
      ARRAY_VALUE(3,1) = GetArrayValue('@CORE.flux[0][2]')
      
      ARRAY_VALUE(1,1) = ARRAY_VALUE(1,1) + 0.1
      ARRAY_VALUE(2,1) = ARRAY_VALUE(2,1) + 0.1
      ARRAY_VALUE(3,1) = ARRAY_VALUE(3,1) + 0.1
                  
      CALL SetArray_Double('@CORE.flux[0][0]', ARRAY_VALUE(1,1), 3*3)
      
      CALL Message('Call Main Proc')
      END 
      
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!     

      SUBROUTINE LOAD_PROC()
                        
      
      END 

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!      
      SUBROUTINE UNLOAD_PROC()
                    
      REAL*8 DATA_VALUE 
      
      
      END       

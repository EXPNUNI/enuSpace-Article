
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      SUBROUTINE MAIN_PROC()

      USE globals                       
      REAL*8 DATA_VALUE 
      REAL*8 ARRAY_VALUE(3,3)
                               
      CALL GetValue('@CORE.flux00', DATA_VALUE)
      
      IF (DATA_VALUE .GT. 1.0) THEN
        DATA_VALUE = 0
      ELSE
        DATA_VALUE = DATA_VALUE+0.01
      ENDIF
        
      CALL SetValue('@CORE.flux00', DATA_VALUE)

      ARRAY_VALUE(1,1) = 0
      ARRAY_VALUE(1,2) = 0
      ARRAY_VALUE(1,3) = 0      
      CALL GetArrayValue('@CORE.flux[0][0]', ARRAY_VALUE(1,1))
      CALL GetArrayValue('@CORE.flux[0][1]', ARRAY_VALUE(2,1))
      CALL GetArrayValue('@CORE.flux[0][2]', ARRAY_VALUE(3,1))
      
      ARRAY_VALUE(1,1) = ARRAY_VALUE(1,1) + 0.1
      ARRAY_VALUE(1,2) = ARRAY_VALUE(1,2) + 0.1
      ARRAY_VALUE(1,3) = ARRAY_VALUE(1,3) + 0.1
                  
      !! #define DEF_DOUBLE	2
      CALL SetArrayValue('@CORE.flux[0][0]', ARRAY_VALUE(1,1), 2, 3*3);
      
      CALL Message('Call Main Proc')
      END 
      
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!     

      SUBROUTINE LOAD_PROC()

      USE globals                       
      REAL*8 DATA_VALUE 
      CHARACTER*32 VARNAME
 
      DATA_VALUE = 0
      CALL SetValue('@CORE.flux00', DATA_VALUE)        
      
      END 

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!      
      SUBROUTINE UNLOAD_PROC()

      USE globals                       
      REAL*8 DATA_VALUE 
      
      
      END       

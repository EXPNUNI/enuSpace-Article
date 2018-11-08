   
MODULE Interface_to_C_Func

   INTERFACE

      SUBROUTINE Message(string) BIND(C, NAME="_Message")
         USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT, C_CHAR, C_PTR, C_DOUBLE
         !.. Return value
           
         !.. Argument list
         CHARACTER(KIND=C_CHAR)     :: string(*)     
      END SUBROUTINE Message 
      
   END INTERFACE

END MODULE Interface_to_C_Func

MODULE IO_DATA
    USE, INTRINSIC :: ISO_C_BINDING
    IMPLICIT NONE

    TYPE :: COMPONENT1
          SEQUENCE
          REAL(C_DOUBLE) :: DUMMY(18)   ! EnuObject Dummy
          INTEGER(C_INT) :: ICOUNT
          REAL(C_DOUBLE) :: FVALUE
          REAL(C_DOUBLE) :: FARRAY(10,5)
    END TYPE COMPONENT1

    TYPE :: COMPONENT2
          SEQUENCE
          REAL(C_DOUBLE) :: DUMMY(18)   ! EnuObject Dummy
          INTEGER(C_INT) :: INPUT
          INTEGER(C_INT) :: OUTPUT
    END TYPE COMPONENT2
    
END MODULE IO_DATA
    
    
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    SUBROUTINE TASK_MAIN_COM1(INPUT) BIND(C,NAME='TASK_MAIN_COM1')

        USE Interface_to_C_Func
        USE IO_DATA
        
        TYPE(COMPONENT1) INPUT

        INPUT.ICOUNT = INPUT.ICOUNT + 1
        INPUT.FVALUE = INPUT.FVALUE + 0.1
        INPUT.FARRAY(1,1) = INPUT.FARRAY(1,1) + 0.1
        
        CALL Message('Call Main Proc-Component1')      

        RETURN
    END
    
    SUBROUTINE TASK_MAIN_COM2(INPUT) BIND(C,NAME='TASK_MAIN_COM2')

        USE Interface_to_C_Func
        USE IO_DATA
        
        TYPE(COMPONENT2) INPUT

        INPUT.INPUT = INPUT.INPUT + 1
        INPUT.OUTPUT = INPUT.INPUT
        
        CALL Message('Call Main Proc-Component2')      

        RETURN
    END    

    SUBROUTINE TASK_INIT
        ! CALL INIT_PROC()
        RETURN
   END  
  
    SUBROUTINE TASK_LOAD
        ! CALL LOAD_PROC()
        RETURN
    END      
    
    SUBROUTINE TASK_UNLOAD
        ! CALL UNLOAD_PROC()
        RETURN
    END 
    
   
    

    

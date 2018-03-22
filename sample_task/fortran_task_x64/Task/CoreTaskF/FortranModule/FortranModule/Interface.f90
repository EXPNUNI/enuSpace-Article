
   MODULE Interface_to_C_Func
 
      INTERFACE
         FUNCTION GetValue(string) BIND(C, NAME="_GetValue")
 
            USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT, C_CHAR, C_PTR, C_DOUBLE
            !.. Return value
            REAL(KIND=C_DOUBLE) :: GetValue                 
            !.. Argument list
            CHARACTER(KIND=C_CHAR)     :: string(*)    
         END FUNCTION GetValue
         
         SUBROUTINE SetValue(string, value) BIND(C, NAME="_SetValue")
            USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT, C_CHAR, C_PTR, C_DOUBLE
            !.. Return value
              
            !.. Argument list
            CHARACTER(KIND=C_CHAR)     :: string(*)
            REAL(KIND=C_DOUBLE)        :: value      
         END SUBROUTINE SetValue 
                 
         FUNCTION GetArrayValue(string) BIND(C, NAME="_GetArrayValue")
            USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT, C_CHAR, C_PTR, C_DOUBLE
            !.. Return value
            REAL(KIND=C_DOUBLE) :: GetArrayValue                 
            !.. Argument list
            CHARACTER(KIND=C_CHAR)     :: string(*)            
         END FUNCTION GetArrayValue
        
         SUBROUTINE SetArray_Double(string, src, isize) BIND(C, NAME="_SetArrayValue_Double")
            USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT, C_CHAR, C_PTR, C_DOUBLE
            !.. Return value            
            !.. Argument list
            CHARACTER(KIND=C_CHAR)     :: string(*)
            REAL(KIND=C_DOUBLE)        :: src
            INTEGER(KIND=C_INT)        :: isize
         END SUBROUTINE SetArray_Double 

         SUBROUTINE SetArray_Float(string, src, isize) BIND(C, NAME="_SetArrayValue_Float")
            USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT, C_CHAR, C_PTR, C_DOUBLE, C_FLOAT
            !.. Return value            
            !.. Argument list
            CHARACTER(KIND=C_CHAR)     :: string(*)
            REAL(KIND=C_FLOAT)        :: src
            INTEGER(KIND=C_INT)        :: isize
         END SUBROUTINE SetArray_Float          
         
         SUBROUTINE SetArray_Int(string, src, isize) BIND(C, NAME="_SetArrayValue_Int")
            USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT, C_CHAR, C_PTR, C_DOUBLE, C_FLOAT
            !.. Return value            
            !.. Argument list
            CHARACTER(KIND=C_CHAR)     :: string(*)
            REAL(KIND=C_INT)        :: src
            INTEGER(KIND=C_INT)        :: isize
         END SUBROUTINE SetArray_Int          
         
         SUBROUTINE Message(string) BIND(C, NAME="_Message")
            USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_INT, C_CHAR, C_PTR, C_DOUBLE
            !.. Return value
              
            !.. Argument list
            CHARACTER(KIND=C_CHAR)     :: string(*)     
         END SUBROUTINE Message 
         
      END INTERFACE
 
   END MODULE Interface_to_C_Func

    
    
      !MODULE globals
      !  USE ISO_C_BINDING
      !  PROCEDURE(), POINTER :: Message
      !  PROCEDURE(), POINTER :: SetValue 
      !  PROCEDURE(), POINTER :: GetValue
      !  PROCEDURE(), POINTER :: SetArrayValue
      !  PROCEDURE(), POINTER :: GetArrayValue
      !END MODULE globals


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      SUBROUTINE MAIN
          CALL MAIN_PROC()
          RETURN
      END
      
      SUBROUTINE LOAD
          CALL LOAD_PROC()
          RETURN
      END      
      
      SUBROUTINE UNLOAD
          CALL UNLOAD_PROC()
          RETURN
      END         
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      !SUBROUTINE 	CALLBACKSETVALUE(fc)
      !    USE ISO_C_BINDING
      !    USE globals
      !
      !    TYPE (C_FUNPTR), VALUE :: fc
      !    CALL C_F_PROCPOINTER(fc, SetValue)
      !END
      !
      !SUBROUTINE 	CALLBACKGETVALUE(fc)
      !    USE ISO_C_BINDING
      !    USE globals
      !
      !    TYPE (C_FUNPTR), VALUE :: fc
      !    CALL C_F_PROCPOINTER(fc, GetValue)
      !END
      !
      !SUBROUTINE 	CALLBACKMESSAGE(fc)
      !    USE ISO_C_BINDING
      !    USE globals
      !
      !    TYPE (C_FUNPTR), VALUE :: fc
      !    CALL C_F_PROCPOINTER(fc, Message)
      !END
      !
      !SUBROUTINE 	CALLBACKGETARRAYVALUE(fc)
      !    USE ISO_C_BINDING
      !    USE globals
      !
      !    TYPE (C_FUNPTR), VALUE :: fc
      !    CALL C_F_PROCPOINTER(fc, GetArrayValue)
      !END
      !
      !SUBROUTINE 	CALLBACKSETARRAYVALUE(fc)
      !    USE ISO_C_BINDING
      !    USE globals
      !
      !    TYPE (C_FUNPTR), VALUE :: fc
      !    CALL C_F_PROCPOINTER(fc, SetArrayValue)
      !END      
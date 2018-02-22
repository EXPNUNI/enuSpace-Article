
      MODULE globals
        USE ISO_C_BINDING
        PROCEDURE(), POINTER :: Message
        PROCEDURE(), POINTER :: SetValue 
        PROCEDURE(), POINTER :: GetValue
        PROCEDURE(), POINTER :: SetArrayValue
        PROCEDURE(), POINTER :: GetArrayValue
      END MODULE globals


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      SUBROUTINE MAIN
          USE globals
          CALL MAIN_PROC()
          RETURN
      END
      
      SUBROUTINE LOAD
          USE globals
          CALL LOAD_PROC()
          RETURN
      END      
      
      SUBROUTINE UNLOAD
          USE globals
          CALL UNLOAD_PROC()
          RETURN
      END         
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      SUBROUTINE 	CALLBACKSETVALUE(fc)
          USE ISO_C_BINDING
          USE globals

          TYPE (C_FUNPTR), VALUE :: fc
          CALL C_F_PROCPOINTER(fc, SetValue)
      END

      SUBROUTINE 	CALLBACKGETVALUE(fc)
          USE ISO_C_BINDING
          USE globals

          TYPE (C_FUNPTR), VALUE :: fc
          CALL C_F_PROCPOINTER(fc, GetValue)
      END
  
      SUBROUTINE 	CALLBACKMESSAGE(fc)
          USE ISO_C_BINDING
          USE globals

          TYPE (C_FUNPTR), VALUE :: fc
          CALL C_F_PROCPOINTER(fc, Message)
      END
      
      SUBROUTINE 	CALLBACKGETARRAYVALUE(fc)
          USE ISO_C_BINDING
          USE globals

          TYPE (C_FUNPTR), VALUE :: fc
          CALL C_F_PROCPOINTER(fc, GetArrayValue)
      END
      
      SUBROUTINE 	CALLBACKSETARRAYVALUE(fc)
          USE ISO_C_BINDING
          USE globals

          TYPE (C_FUNPTR), VALUE :: fc
          CALL C_F_PROCPOINTER(fc, SetArrayValue)
      END      
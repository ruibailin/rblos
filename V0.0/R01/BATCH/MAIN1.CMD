-OUTPUT(..\object\main.omf)  &  Output filename
-bootstrap                &
-PRINT                    &  Output print file
-ONEBLKDEF                &  Generate one BLKDEF record for each procedure
-SORTLINE                 &  Sort Line numbers
-ORDER(CLASSES(           &  Order segments by their class names
          FAR_DATA_BEG,   &
          FAR_DATA,       &
          FAR_DATA_END,   &
          FAR_BSS_BEG,    &
          FAR_BSS,        &
          FAR_BSS_END,    &
          HUGE_BSS_BEG,   &
          HUGE_BSS,       &
          HUGE_BSS_END,   &
          DATA_BEG,       &
          DATA,           &
          CONST,          &
          MSG,            &
          DATA_END,       &
          BSS,            &
          BSS_END,        &
          STACK,          &
          CODE,           &
          SSI_ROMINIT) )  &
                          &
-ROMINIT(CLASSES(DATA,    &  Move these segments into SSI_ROMINIT  
    CONST,MSG,FAR_DATA))  &  This order must match the order in STARTUP.ASM
                          &  that copies initialized data from ROM to RAM
-ADDRESSES(CLASSES(       &  Specify addresses by class names
    FAR_DATA_BEG(00200H), &
    CODE(F0000H) )  )     &  Notes and comments are to right of ampersand.

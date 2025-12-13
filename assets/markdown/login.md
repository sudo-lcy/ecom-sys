flowchart TD
    %% Define styles
    classDef startend fill:#fff,stroke:#000,stroke-width:2px,rx:10,ry:10;
    classDef io fill:#fff,stroke:#000,stroke-width:1px,slant:45;
    classDef decision fill:#fff,stroke:#000,stroke-width:1px,shape:diamond;
    classDef process fill:#fff,stroke:#000,stroke-width:1px;

    Start([Start]) --> DisplayRoles[/Display Login Menu/]
    DisplayRoles --> InputRole[/Input Role/]
    
    %% Role Validation Loop
    InputRole --> ValidRole{Role 0, 1, or 2?}
    ValidRole -- No --> MsgInvalidRole[/Display 'Invalid Role'/]
    MsgInvalidRole --> InputRole
    
    %% Exit Check
    ValidRole -- Yes --> CheckExit{Role == 0?}
    CheckExit -- Yes --> RetFalse([Return False])
    
    %% BRANCH: Admin vs Customer
    CheckExit -- No --> CheckAdmin{Role == 1?}
    
    %% === ADMIN PATH ===
    CheckAdmin -- Yes --> AdminInit[Set i = 0]
    AdminInit --> AdminLoop{i < 3?}
    
    AdminLoop -- True --> AdminInput[/Input Admin Username & Password/]
    AdminInput --> AdminCheck{Matches ADMIN_CREDS?}
    
    AdminCheck -- Yes --> SetAdmin[isAdmin = true]
    SetAdmin --> RetTrue([Return True])
    
    AdminCheck -- No --> AdminMsg[/Display 'Invalid Admin Creds'/]
    AdminMsg --> AdminInc[i = i + 1]
    AdminInc --> AdminLoop
    
    AdminLoop -- False --> FailMsg[/Display 'Too many failed attempts'/]
    FailMsg --> RetFalse

    %% === CUSTOMER PATH ===
    CheckAdmin -- No --> CustInit[Set i = 0]
    CustInit --> CustLoop{i < 3?}
    
    CustLoop -- True --> CustInput[/Input Customer Username & Password/]
    CustInput --> CustCheck{Matches CUST_CREDS?}
    
    CustCheck -- Yes --> SetCust[isAdmin = false]
    SetCust --> RetTrue
    
    CustCheck -- No --> CustMsg[/Display 'Invalid Customer Creds'/]
    CustMsg --> CustInc[i = i + 1]
    CustInc --> CustLoop
    
    CustLoop -- False --> FailMsg

    %% Apply styles
    class Start,RetFalse,RetTrue startend;
    class DisplayRoles,InputRole,MsgInvalidRole,AdminInput,AdminMsg,CustInput,CustMsg,FailMsg io;
    class ValidRole,CheckExit,CheckAdmin,AdminLoop,AdminCheck,CustLoop,CustCheck decision;
    class AdminInit,AdminInc,SetAdmin,CustInit,CustInc,SetCust process;
flowchart TD
    %% Define styles to match PDF logic
    classDef startend fill:#fff,stroke:#000,stroke-width:2px,rx:10,ry:10;
    classDef process fill:#fff,stroke:#000,stroke-width:1px;
    classDef io fill:#fff,stroke:#000,stroke-width:1px,slant:45;
    classDef decision fill:#fff,stroke:#000,stroke-width:1px,shape:diamond;
    classDef func fill:#fff,stroke:#000,stroke-width:1px,stroke-dasharray: 0, shape:rect; 
    %% Creating the double vertical line effect for function calls is hard in standard mermaid, 
    %% so we use standard rectangles but denote them clearly as Call [Function].

    Start([Start]) --> CallArray[[Call arrayProducts]]
    CallArray --> LoginStart
    
    subgraph MainLoop [Main Application Loop]
        LoginStart(Login Start) --> CallLogin[[Call login]]
        CallLogin -- Returns False --> Goodbye[/Display Goodbye/]
        Goodbye --> End([End])
        
        CallLogin -- Returns True --> CheckAdmin{isAdmin?}
        
        CheckAdmin -- Yes --> CallAdmin[[Call adminMenu]]
        CheckAdmin -- No --> CallCust[[Call customerMenu]]
        
        CallAdmin --> AskAgain[/Display 'Login again? y/n'/]
        CallCust --> AskAgain
        
        AskAgain --> InputAgain[/Read input 'again'/]
        InputAgain --> CheckAgain{again == 'n'?}
    end

    CheckAgain -- True --> End
    CheckAgain -- False --> LoginStart
    
    class Start,End startend;
    class InputAgain,Goodbye,AskAgain io;
    class CheckAdmin,CheckAgain decision;
    class CallArray,CallLogin,CallAdmin,CallCust func;
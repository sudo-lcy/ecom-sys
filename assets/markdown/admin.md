flowchart TD
    Start([Start]) --> DisplayMenu[/Display Admin Menu/]
    DisplayMenu --> InputChoice[/Read Choice/]
    
    InputChoice --> CheckChoice{Switch Choice}
    
    CheckChoice -- 1 --> View[[Call displayAllProducts]]
    CheckChoice -- 2 --> Search[[Call searchProductByName]]
    CheckChoice -- 3 --> Add[[Call addProduct]]
    CheckChoice -- 4 --> Update[[Call updateProduct]]
    CheckChoice -- 5 --> Delete[[Call deleteProduct]]
    CheckChoice -- 0 --> Logout[/Display 'Logging out'/]
    CheckChoice -- Default --> Invalid[/Display 'Invalid Choice'/]
    
    View --> LoopCheck
    Search --> LoopCheck
    Add --> LoopCheck
    Update --> LoopCheck
    Delete --> LoopCheck
    Invalid --> LoopCheck
    
    LoopCheck{Choice != 0?}
    LoopCheck -- True --> DisplayMenu
    LoopCheck -- False --> Ret([Return])
    Logout --> Ret

    classDef startend fill:#fff,stroke:#000,stroke-width:2px,rx:10,ry:10;
    class Start,Ret startend;
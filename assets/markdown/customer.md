flowchart TD
    Start([Start]) --> DisplayMenu[/Display Customer Menu/]
    DisplayMenu --> InputChoice[/Read Choice/]
    
    InputChoice --> CheckChoice{Switch Choice}
    
    CheckChoice -- 1 --> View[[Call displayAllProducts]]
    CheckChoice -- 2 --> Search[[Call searchProductByName]]
    CheckChoice -- 3 --> CartAdd[[Call addToCart]]
    CheckChoice -- 4 --> CartView[[Call viewCart]]
    CheckChoice -- 5 --> CheckoutCall[[Call checkout]]
    CheckChoice -- 0 --> Logout[/Display 'Logging out'/]
    
    View & Search & CartAdd & CartView --> LoopCheck
    
    %% Checkout Logic Visualization
    subgraph CheckoutProcess [Checkout Logic]
        CheckoutCall --> EmptyCheck{Is Cart Empty?}
        EmptyCheck -- Yes --> MsgEmpty[/Display 'Empty'/]
        EmptyCheck -- No --> Calc[[Call calculateTotals]]
        Calc --> ShowTotal[/Display Totals/]
        ShowTotal --> Confirm[/Read 'Proceed? y/n'/]
        Confirm --> ConfCheck{Ans == 'y'?}
        ConfCheck -- Yes --> Process[Reduce Stock & Clear Cart]
        Process --> MsgSuccess[/Display Success/]
        ConfCheck -- No --> MsgCancel[/Display Cancelled/]
    end
    
    MsgEmpty & MsgSuccess & MsgCancel --> LoopCheck
    
    LoopCheck{Choice != 0?}
    LoopCheck -- True --> DisplayMenu
    LoopCheck -- False --> Ret([Return])
    Logout --> Ret

    classDef startend fill:#fff,stroke:#000,stroke-width:2px,rx:10,ry:10;
    class Start,Ret startend;
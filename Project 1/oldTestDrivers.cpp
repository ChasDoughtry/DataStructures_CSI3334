/*
// Location testing
    Location A;
    Location B;

    //Testing == operator
    if(A == B){
        cout << "A & B are equal" << endl;
    }

    cout << "A: " << A << endl;
    cout << "Neighbors of A: " << endl;
    for (A.iterationBegin(); !A.iterationDone(); A.iterationAdvance()) {
        Location neighbor = A.iterationCurrent();
        cout << neighbor << endl;
    }
    cout << endl;

    //Testing >>  and << operator
    cin >> A;
    cout << "New A: " << A;

// Maze testing
    Maze theMaze;
    Location end;
    cin >>end;

    cin >> theMaze;

    cout << endl << "start " << theMaze.getStartLocation() << endl;


    if (theMaze.isEndLocation(end)){
        cout << "end is 0 0";
    }



    LocationStack st;
    Location* locs;
    Location startL, endLoc;
    int n;

    cin >> n;
    locs = new Location [n];

    for(int i = 0; i < n; ++i){
        cin >>locs[i];
        //st.push(locs[i]);
    }
    cin >> startL >> endLoc;

    for (int i = 0; i < n; i++){
        st.push(locs[i]);
    }


    cout << "locations:" << endl;


    for(int i = 0; i < n; ++i){
        cout << locs[i] << endl;
    }


    cout << "top1: " << endl;
    cout << st.getTop() << endl;

    cout << "top2: " << endl;
    //st.pop();
    cout << st.getTop() << endl;

    cout << "stack: " << endl;

    cout << st;


    delete[] locs;
    */
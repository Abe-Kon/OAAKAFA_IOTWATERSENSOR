char page[] PROGMEM = R"(
  <!DOCTYPE html>

<html>

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>midsemproject</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <!--<link href="style.css" rel="stylesheet" type="text/css" />-->
    <meta name="Author" content="Akwasi Fredua Agyemang">
    <style>
        body {
            font-family: Arial;
            text-align: center
        }

       
        /* .btn {
            display: block;
            width: 280px;
            margin: auto;
            padding: 30px
        } */

        /* .btn {
            font-size: 30px;
            color: black;
            text-decoration: none
        } */
        
        .on {
            background-color: SkyBlue
        }

        .off {
            background-color: LightSteelBlue
        }

        .zero {
            background-color: Thistle
        }
        .center 
        {
            margin-left: auto;
            margin-right: auto;
        }
       
        body {
        background-color:#BDB7C9;
       }
        th,td {
            font-size: 30px;
            margin-top: 50px;
            margin-bottom: 5px;
            padding-top: 10px;
            padding-bottom: 20px;
            padding-left: 30px;
            padding-right: 40px;
            border-color: #FFFFFF;
        }    

        p {
            font-size: 30px;
            margin-top: 50px;
            margin-bottom: 5px
        }
    </style>
</head>

<body>
    <nav class="navbar bg-light">
        <div class="container-fluid">
        <a class="navbar-brand" href="#">
            <div class="container-fluid" style="text-align: center;">
                <img src="iot_logo.jpg" alt="Logo" width="30" height="25" class="d-inline-block align-text-top">
            <!-- <h4> -->
                IOT PROJECT BY AKWASI, JIL AND ABENA
            <!-- </h4> -->
            </div> 
        </a>
    </nav>
    <section>
        <h1 class="display-1">
            <p1>Water Level Dashboard</p1><br />
        </h1>

        <h1 class="text-muted"><em>Illustrating AJAX fetch of dynamic content</em></h1>
        <div class="alert alert-dark" role="alert">
            We will fetch details of one particular record in the db. You can enter an ID if you know one (eg id=1,...,6)
          </div>

            <p><div id="waterworks">init</div></p>
          
          </section>

    
    
    <br /><br />

          <br /><br />
    <h1 style="color:White;" id="stat" onclick='sendData(id)' class="display-4">Operation Mode</h1>
    <table style='width:100%;margin-bottom: 10px;'>
        <tr>
            <th scope="col" style='width:50%'><h3>Manual</h3></th>
            <th scope="col"><h3>Automatic</h3></th>
        </tr>
        <tr>
           <!-- <td><button pill class='btn off btn-secondary col-2' id='Green LED' onclick='sendData(id)'>OFF</button> -->
          <td><button pill class="btn off btn-secondary btn-sm" type="button" id='Start' onclick='sendData_2(id)'>START</button></td>
          <td><button pill class="btn on btn-secondary col-2" id='Gren LED' onclick='sendData(id)'>ON</button></td> 

        </tr>
        <tr>
            <td>
                <div class="d-grid gap-1 col-1 mx-auto">
                <button pill class="btn off btn-secondary btn-sm" type="button" id='Stop' onclick='sendData_2(id)'>STOP</button>
              </div>
        </tr>
            
    </table>
           
                
                
           



        <script>
            function autoStart(butn){
                var URL,variab,text;
                if (butn =='Automatic'){
                    URL = 'Automatic';
                }
                var xhr = new XMLHttpRequest();
                xhr.onreadystatechange = function (butn){
                    if(this.readyState == 4 && this.status == 200){
                        document.getElementById(variab).innerHTML =this.responseText;};
                        xhr.open('GET',URL,true);
                        xhr.send();
                }
            }
            function manStart(butn){
                var URL,variab,text;
                if (butn =='Start'){
                    URL = 'Start';
                }
                var xhr = new XMLHttpRequest();
                xhr.onreadystatechange = function (butn){
                    if(this.readyState == 4 && this.status == 200){
                        document.getElementById(variab).innerHTML =this.responseText;};
                        xhr.open('GET',URL,true);
                        xhr.send();
                }
            }
            function manStop(butn){
                var URL,variab,text;
                if (butn =='Stop'){
                    URL = 'Stop';
                }
                var xhr = new XMLHttpRequest();
                xhr.onreadystatechange = function (butn){
                    if(this.readyState == 4 && this.status == 200){
                        document.getElementById(variab).innerHTML =this.responseText;};
                        xhr.open('GET',URL,true);
                        xhr.send();
                }
            }
            function state_activate(x){
                    var state = document.getElementById(x).className;
                    state = (state == 'btn on' ? 'btn off' : 'btn on');
                    text = (state == 'btn on' ? ' OFF' : ' ON');
                    document.getElementById(x).className = state;
                    document.getElementById(x).innerHTML = text;
                }
            
            function state_deactivate(x){
                var state = document.getElementById(x).className;
                    state = (state == 'btn off');
                    text = (state == ' OFF');
                    document.getElementById(x).className = state;
                    document.getElementById(x).innerHTML = text;
            }

            function sendData_2(butn2){
                var URL, variab, text;
                URL = 'LEDGurl';
                variab = 'LEDG';
                if (butn2 == 'Start') {
                    //var state = document.getElementById(butn2).className;
                    //state = (state == 'btn on' ? 'btn off' : 'btn on');
                    //text = (state == 'btn on' ? ' Start' : ' Start');
                    //document.getElementById(x).className = state;
                    //document.getElementById(x).innerHTML = text;
                    //state_activate(butn2);
                    URL = 'Start';
                }
                if (butn2 == 'Stop'){
                    //var state = document.getElementById(butn2).className;
                    //state = (state == 'btn on' ? 'btn off' : 'btn on');
                    //text = (state == 'btn on' ? ' Stop' : ' Stop');
                    //document.getElementById(x).className = state;
                    //document.getElementById(x).innerHTML = text;
                    //state_activate(butn2);
                    URL = 'Stop';
                }

                var xhr = new XMLHttpRequest();
                xhr.onreadystatechange = function (butn) {
                    if (this.readyState == 4 && this.status == 200)
                        document.getElementById(variab).innerHTML = this.
                            responseText;
                };
                xhr.open('GET', URL, true);
                xhr.send();
            }

            function sendData(butn) {
                var URL, variab, text;
                // automatic
                if (butn == 'Gren LED') { 
                    URL = 'Automatic';
                    variab = 'LEDR';
                    state_activate(butn);
                    //state_deactivate('Gren Led');
                }
                // manual
                else{// if (butn == 'Green LED')
                    URL = 'LEDGurl';
                    variab = 'Automatic';
                    state_activate(butn);
                    state_deactivate('Gren Led');
                    if(butn == 'Start'){
                        sendData_2('Start');
                    }
                    else{
                        sendData_2('Stop');
                    }
                }
                var xhr = new XMLHttpRequest();
                xhr.onreadystatechange = function (butn) {
                    if (this.readyState == 4 && this.status == 200)
                        document.getElementById(variab).innerHTML = this.
                            responseText;
                };
                xhr.open('GET', URL, true);
                xhr.send();
            }

            setInterval(reload, 1000);
            function reload() {
                var xhr = new XMLHttpRequest();
              xhr.onload=function(){
                console.log(this.responseText);
                document.getElementById("waterworks").innerHTML=this.responseText;
            }
                xhr.open('GET', 'sendData', true);
                xhr.send();
            }
        </script>

            <script type="text/javascript">
        var counter=0;
        function updateByJS(){
            counter++;
            document.getElementById("js_update").innerText="This is the New Text, number of times pressed ="+counter;
        }

        function updateByAJAX_static(){
            const xhttp=new XMLHttpRequest();
            xhttp.onload=function(){
                document.getElementById("statictext").innerText=this.responseText;
            }
            xhttp.open("GET", "/iot/get.php");
            xhttp.send();
        }


        function updateByAJAX_dbData(){
            const xhttp=new XMLHttpRequest();
            xhttp.onload=function(){
                console.log(this.responseText);
                document.getElementById("waterworks").innerHTML=this.responseText;
            }
            id=document.getElementById("theText").value;
            console.log(id);
            
            var url = 

            xhttp.open("GET", "/iot/get.php?owner_id="+id);
            xhttp.send();
        }

    
        </script>

    </section>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
</body>

</html>

)";
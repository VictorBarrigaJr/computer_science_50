/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// track passangers
var FULL = -1;
var PEOPLE = 0;
var MARKERS = [];
var PLACEMARKS = [];
var LONGLAT = [];

// timer
var TIME = 99;
var COUNTER;

// points
var POINTS = 0;

// total passangers - 3 freshman = 99
var TOTAL_PASSENGERS = 99;

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });
    /*
    $("#teleport").on("click" ,function() {
        teleport();
    });
    */
    // load application
    load();
    
});

// unload application
$(window).unload(function() {
    unload();
});

/**
 * Renders seating chart.
 */
function chart()
{
    var html = "<ol start='0'>";
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li>Empty Seat</li>";
        }
        else
        {
            html += "<li>" + shuttle.seats[i].name + " ("+ shuttle.seats[i].house + ")</li>";
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    var droped_off = false;
    
    // if shuttle is empty
    if (PEOPLE == 0)
    {
        $("#announcements").html("The shuttle is currently empty. You need to pick up a passanger before you can drop one off.");
        return;
    }
    else
    {    
        // iterate through all seats in shuttle for passanger to dropoff
        for (var i = 0; i < shuttle.seats.length; i++)
        {
            // if seat is not empty
            if (shuttle.seats[i] != null)
            {
                // assign the passangers house to house var
                var house = shuttle.seats[i].house;
                // if house is within distance of 30 meters, release passangers, release passanger
                if (shuttle.distance(HOUSES[house].lat, HOUSES[house].lng) < 30)
                {
                    shuttle.seats[i] = null;
                    droped_off = true;
                    TIME += 60;
                    POINTS += 100;
                    PEOPLE--;
                    TOTAL_PASSENGERS--;
                    $("#announcements").html("Passenger dropped off.");
                    chart();                
                }            
            }
        } 
    }
    if (TOTAL_PASSENGERS == 0)
    {
        POINTS += 9999;
        $("#announcements").html("There are no passangers! You have picked up and dropped off all of them!");  
    }
    if (!droped_off)
    {
      $("#announcements").html("There are no passangers within 30 meters of their homes.");  
      POINTS -= 25;
      TIME -= 25;
    }
}

/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        return false;
    }
  
    return true;
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/**
 * Picks up nearby passengers.
 */
function pickup()
{
    var picked_up = false;
    // verify seat is available for passanger, if available assign and pick up passanger, else rtn message
    var seat = seat_search();
    if (seat != FULL)
    {           
        // get earth features to remove placemark
        var features = earth.getFeatures();

        //  find passanger by iterating through PASSENGERS  
        for (var i = 0; i < PASSENGERS.length; i++)
        {             
            // if passanger is within range, pick up
            if (shuttle.distance(LONGLAT[i].latitude, LONGLAT[i].longitude) < 15)
            {
                if (!(PASSENGERS[i].house in HOUSES))
                {
                    $("#announcements").html("The passanger is a freshman. Your not allowed to pick up freshman.");
                    TIME -= 25;
                    POINTS -= 25;
                    return;
                }
                else
                {
                    // remove placemark, marker, assign shuttle seat to passanger
                    features.removeChild(PLACEMARKS[i]);
                    PLACEMARKS[i] = null;
                    MARKERS[i].setMap(null);
                    shuttle.seats[seat] = PASSENGERS[i];
                    PEOPLE ++;
                    TIME += 15;
                    POINTS += 10;
                    picked_up = true;
                }
            }    
            
            seat = seat_search();            
        }
    }  
    // shuttle full
    else
    {        
        $("#announcements").html("The shuttle is currently full. You need to drop off a passanger before you can pick a passanger.");
        TIME -= 25;
        POINTS -= 25;
        return;
    }
    
    if (!picked_up)
    {
        $("#announcements").html("There are no passangers within 15 meters.");
    }
    else
    {
        $("#announcements").html("Passenger picked up.");
    }
    
    chart();
}

/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });

        // remember passenger's placemark and marker for pick-up's sake
        MARKERS.push(marker);
        PLACEMARKS.push(placemark);
        LONGLAT.push({longitude: building.lng, latitude: building.lat});
        PEOPLE++;
    }
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}

/**
 * returns the available seat one null, or -1 on full
 */
function seat_search()
{
    for(var i = 0; i < shuttle.seats.length; i++)
    {
        if(shuttle.seats[i] == null)
        {
            return i;
        }
    }
    return FULL;
}

/**
 * countdown timer
 */
function timer()
{
    TIME = TIME - 1;
    // timer reaches zero, relaunch timer.
    if (TIME == 0)
    {
        TIME += 99;
        COUNTER = setInterval(timer,1000);
        timer();
        POINTS = POINTS / 2;
        $("#announcements").html("Time ended, you were not fast enough. You lost half your points!");
        return;
    }
    // display timer
    document.getElementById("timer").innerHTML = TIME;
    document.getElementById("points").innerHTML = POINTS;
}

/**
 * shows instructions at start engine and starts timer.
 */
function start_enginge()
{
    alert("Vroom vroom! Don't click the 3D Earth, else the engine may stall, in which case you'll need to re-start it! CLICK OK to START the timer.");
    COUNTER = setInterval(timer, 1000);
}
/**
 * teleports shuttle to selected buildings
 */
function teleport() 
{
    var teleport_to = document.getElementById("go_to").value;
    if (teleport_to == "915")
    {
         
        alert("You need to select a building from the dropdown menu.");
    }
    else
    {
        // instantiate shuttle at new location
        shuttle.position.heading = HEADING;
        shuttle.position.latitude = HOUSES[teleport_to].lat;
        shuttle.position.longitude = HOUSES[teleport_to].lng;
        shuttle.localAnchorCartesian =  V3.latLonAltToCartesian([shuttle.position.latitude, shuttle.position.longitude, shuttle.position.altitude]);
    }
}

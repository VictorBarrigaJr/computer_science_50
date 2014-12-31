var api_key = '';
var api_secret = '';


lastfmSession = undefined;
userName = undefined;
scrobbleOn = false;

$.cookie.json = true;

function logError(code, message) {
    console.log('Error ('+code+'): '+message);
}

function initLastfm() {
    /* Create a LastFM object */
    lastfm = new LastFM({
      apiKey    : api_key,
      apiSecret : api_secret
    });
}
function initToken() {
    lastfm.auth.getToken({
        success: function(data) {
            var win = window.open('https://www.last.fm/api/auth/?api_key='+api_key+'&token='+data.token, "Connect LastFM", "width=1000");
            var timer = setInterval(function() {
                if(win.closed) {
                    clearInterval(timer);
                    initSession(data.token);
                }
            }, 1000);
        },
        error: function(code, message) {
            logError(code, message);
        }
    });
}
function initSession(authToken) {

    if (typeof $.cookie('lastfm-session') != 'undefined') {
        setSession($.cookie('lastfm-session'));
    }
    else if (typeof authToken != 'undefined') {
        lastfm.auth.getSession({token: authToken}, {
            success: function(data) {
                setSession(data.session);
            },
            error: function(code, message) {
                logError(code, message);
            }
        });
    }
}
function setSession(session) {
    lastfmSession = session;
    $.cookie('lastfm-session', session, {
        expires: 365
    });
}
function toggleScrobble(set) {
    $.cookie('lastfm-scrobble', set);
    scrobbleOn = set;
    $('#toggleScrobble').prop('checked', set);
    $('#toggleScrobble').button('refresh');
    if (set) {
        // Initialise session
        if (typeof lastfmSession == 'undefined') {
            initToken();
        }
    }
}

function timestamp() {
    return Math.floor(Date.now() / 1000);
}

function nowPlaying(artist, track, duration) {
    if (scrobbleOn) {
        lastfm.track.updateNowPlaying({
                artist: artist,
                track: track,
                duration: duration
            },
            lastfmSession,
            {
                success: function(data) {
                    console.log(data);
                },
                error: function(code, message) {
                    logError(code, message);
                }
            }
        );
    } else{
        logError(0, 'Scrobbling disabled');
    }
}
function scrobble(artist, track, timestamp) {
    if (scrobbleOn) {
        lastfm.track.scrobble({
            artist: artist,
            track: track,
            timestamp: timestamp,
            chosenByUser: 0,
            },
            lastfmSession,
            {
                success: function(data) {
                    console.log(data);
                },
                error: function(code, message) {
                    logError(code, message);
                }
            }
        );
    } else{
        logError(0, 'Scrobbling disabled');
    }
}


$(function() {
    $('#toggleScrobble').prop('checked', $.cookie('lastfm-scrobble'));
    scrobbleOn = $.cookie('lastfm-scrobble');


    $('label[for="toggleScrobble"]').text('');
    $('#toggleScrobble').button().click(function() {
        if ($(this).is(':checked')) {
            toggleScrobble(true);
        } else{
            toggleScrobble(false);
        }
        
    });

    initLastfm();
    initSession();
});
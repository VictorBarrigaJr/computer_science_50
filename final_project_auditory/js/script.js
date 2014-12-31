/**
 * scripts.js 
 *
 * Computer Science 50
 * Problem Set: Final Project
 * Project Name: Auditory (c) by Victor Barriga
 *
 * Global JavaScript.
 */
 
$(document).ready(function() {
    // jQuery to collapse the navbar on scroll
    $(window).scroll(function() {
        if ($(".navbar").offset().top > 50) {
            $(".navbar-fixed-top").addClass("top-nav-collapse");
        } else {
            $(".navbar-fixed-top").removeClass(
                "top-nav-collapse");
        }
    });
    // jQuery for page scrolling feature - requires jQuery Easing plugin
    $(function() {
        $('a.page-scroll').bind('click', function(event) {
            var $anchor = $(this);
            $('html, body').stop().animate({
                scrollTop: $($anchor.attr(
                    'href')).offset().top
            }, 1500, 'easeInOutExpo');
            event.preventDefault();
        });
    });
    // Closes the Responsive Menu on Menu Item Click
    $('.navbar-collapse ul li a').click(function() {
        $('.navbar-toggle:visible').click();
    });    
    // function scrolls to a particular target on the page
    $.fn.scrollTo = function(target, options, callback) {
            if (typeof options == 'function' && arguments.length == 2) {
                callback = options;
                options = target;
            }
            var settings = $.extend({
                scrollTarget: target,
                offsetTop: 50,
                duration: 500,
                easing: 'swing'
            }, options);
            return this.each(function() {
                var scrollPane = $(this);
                var scrollTarget = (typeof settings.scrollTarget ==
                    "number") ? settings.scrollTarget : $(
                    settings.scrollTarget);
                var scrollY = (typeof scrollTarget == "number") ?
                    scrollTarget : scrollTarget.offset().top +
                    scrollPane.scrollTop() - parseInt(settings.offsetTop);
                scrollPane.animate({
                        scrollTop: scrollY
                    }, parseInt(settings.duration),
                    settings.easing, function() {
                        if (typeof callback == 'function') {
                            callback.call(this);
                        }
                    });
            });
        }
    
    // function queries lastfm with on users search request
    function doClick() {
            // check if form is empty
            if ($('input:text').val().length == 0) {
                $(this).parents('p').addClass('warning');
                alert("Search field cannot be empty");
                return;
            }
            $('#search_results').hide();
            // define api keys
            var apiKey = 'c7723045bd1407937dd5699df5218371';
            var apiSecret = 'b8b03d43248e529eae356d5beb20d052';
            // create a Cache object
            var cache = new LastFMCache();
            // create a LastFM object
            var lastfm = new LastFM({
                apiKey: apiKey,
                apiSecret: apiSecret,
                cache: cache
            });
            var topArtistName = '';
            var similarArtists = '';
            var searchArtistName = document.getElementById("search_for")
                .value;
            // query results from lastfm based on user input
            if (searchArtistName !== null) {
                // load details of the artist searched
                lastfm.artist.getInfo({
                    artist: searchArtistName
                }, {
                    success: function(data) {
                        // render the artist info
                        $('#searched_artist_bio').html($(
                            '#lastfmTemplateSearchedArtistBio'
                        ).render(data.artist));
                        $('#searched_artist_pic').html($(
                            '#lastfmTemplateSearchedArtistPic'
                        ).render(data.artist));
                    }
                });
                // similar artists query list based on user input 
                lastfm.artist.getSimilar({
                    limit: 12,
                    artist: searchArtistName,
                    autocorrect: 1
                }, {
                    success: function(data) {
                        // for each similar artist get full info with active links
                        $.each(data.similarartists.artist, function(i, item) {
                                // queries and loads details of the artist searched
                                lastfm.artist.getInfo({
                                    artist: data.similarartists.artist[i].name
                                }, {
                                    success: function(data) {
                                        // render the artist info         
                                        $('#similar_artist_bio' + '_' + i).html($(
                                            '#lastfmTemplateSimilarArtistBio'
                                        ).render(data.artist));
                                    }
                                });
                            });
                    }
                });
                // displays the search results to page
                $(document).ready(function() {
                    $('#search_results').show('slow');
                    $('body').scrollTo('#search_results', {
                        duration: 'slow',
                        offsetTop: '10'
                    });
                });
            }
            return false;
        }
    // detects the press of button on surch bar
    $('#search_fm').click(doClick);
    // detects the pressing of the enter key on the search bar
    $('#search_for').keypress(function(e) {
        var key = e.which;
        if (key == 13) // the enter key code
        {
            doClick();
        }
    });
});
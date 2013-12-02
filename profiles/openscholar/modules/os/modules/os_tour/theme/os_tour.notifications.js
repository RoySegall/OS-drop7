/**
 * jQuery behaviors for platform notification feeds.
 */
(function ($) {
  Drupal.behaviors.os_notifications = {
    attach: function (context) {

      // Setup.
      var menuLinkSel = '#os-tour-notifications-menu-link';
      if ($(menuLinkSel + '.os-notifications-processed').length) {
        return;
      }
      $(menuLinkSel).attr('href', '#').text('').addClass('os-notifications-processed');
      var settings = Drupal.settings.os_notifications;
      if (typeof google == 'undefined') {
        return;
      }

      // @TODO: Add support for multiple feeds.
      var feed = new google.feeds.Feed(settings.url);
      var items = [];
      feed.setNumEntries(settings.max);
      feed.load(function (result) {
        if (!result.error) {
          for (var i = 0; i < result.feed.entries.length; i++) {
            var num_remaining = (result.feed.entries.length - i);
            var entry = result.feed.entries[i];
            if (os_tour_notifications_is_new(entry)) {
              var item = os_tour_notifications_item(entry, num_remaining);
              items.push(item);
            }
          }

          // Only continues if we have the hopscotch library defined.
          if (typeof hopscotch == 'undefined') {
            return;
          }

          // If there are items to display in a hopscotch tour...
          if (items.length) {
            // Sets up the DOM elements.
            $(menuLinkSel).append($("<i class='os-tour-notifications-icon'/>"));
            $(menuLinkSel).append($("<span id='os-tour-notifications-count'/>"));
            os_tour_notifications_count(items.length);
            $('#os-tour-notifications-menu-link').slideDown('slow');
            // Sets up the tour object with the loaded feed item steps.
            var tour = {
              showPrevButton: true,
              scrollTopMargin: 100,
              id: "os-tour-notifications",
              steps: items,
              onEnd: function() {
                os_tour_notifications_count(-1);
                os_tour_notifications_read_update();
              }
            };

            // Adds our tour overlay behavior with desired effects.
            $('#os-tour-notifications-menu-link').click(function() {
              $('html, body').animate({scrollTop:0}, '500', 'swing', function() {
                $('.hopscotch-bubble').addClass('animated');
                hopscotch.startTour(tour);
                // Removes animation for each step.
                $('.hopscotch-bubble').removeClass('animated');
                // Allows us to target just this tour in CSS rules.
                $('.hopscotch-bubble').addClass('os-tour-notifications');
              });
            });
          }
        }
      });
    }
  };

  /**
   * Determines if the feed item is new enough to display to this user.
   *
   * @param {object} entry
   * @returns {bool}
   */
  function os_tour_notifications_is_new(entry) {
    var pub_date = new Date(entry.publishedDate);
    var pub_date_unix = pub_date.getTime() / 1000;
    var last_read = Drupal.settings.os_notifications.last_read;
    if (pub_date_unix > last_read) {
      return true;
    }

    return false;
  }

  /**
   * Converts a Google FeedAPI Integration feed item into a hopscotch step.
   *
   * @param {object} entry
   * @returns {string} output
   */
  function os_tour_notifications_item(entry, num_remaining) {
    // Prepare the output to display inside the tour's content region.
    var output = "<div class='feed_item'>";

    // Adds a date like "5 days ago", or blank if no valid date found.
    var date = "";
    /** @FIXME parse entry.contentSnippet to see if it starts with a date first.
    if (typeof entry.publishedDate != 'undefined' && entry.publishedDate != '') {
      date = os_tour_notifications_fuzzy_date(entry.publishedDate);
      if (typeof date === 'undefined') {
        date = "";
      } else {
        date = "<span class='date'>" + date + "</span>";
      }
    }
    */
    output += date;

    // Builds the remainder of the content, with a "Read more" link.
    output += "<span class='description'>";
    var content = entry.content;
    if (typeof entry.contentSnippet != 'undefined') {
      content = entry.contentSnippet;
    }
    output += content + "</span>";
    output += '<div class="os-tour-notifications-readmore"><a target="_blank" href="' + entry.link + '">Read more &raquo;</a></div></div>';

    // Returns the item to be added to the tour's (array) `items` property .
    var item = {
      title: entry.title,
      content:output,
      target: document.querySelector("#os-tour-notifications-menu-link"),
      placement: "bottom",
      yOffset: -3,
      xOffset: -10,
      onShow: function() {
        os_tour_notifications_count(num_remaining)
      }
    };
    return item;
  }

  /**
   * Takes an ISO time and returns a string with "time ago" version.
   *
   * @param time
   * @returns {string}
   */
  function os_tour_notifications_fuzzy_date(time) {
    var date = new Date(time),
      diff = (((new Date()).getTime() - date.getTime()) / 1000),
      day_diff = Math.floor(diff / 86400);

    if (isNaN(day_diff) || day_diff < 0 || day_diff >= 31) {
      return;
    }

    return day_diff == 0 && (
      diff < 60 && "just now" ||
        diff < 120 && "1 minute ago" ||
        diff < 3600 && Math.floor(diff / 60) + " minutes ago" ||
        diff < 7200 && "1 hour ago" ||
        diff < 86400 && Math.floor(diff / 3600) + " hours ago") ||
      day_diff == 1 && "Yesterday" ||
      day_diff < 7 && day_diff + " days ago" ||
      day_diff < 31 && Math.ceil(day_diff / 7) + " weeks ago";
  }

  /**
   * Updates the notifications count of remaining notifications.
   */
  function os_tour_notifications_count(num_remaining) {
    var count = '#os-tour-notifications-count';
    var value = parseInt($(count).text());
    if (arguments.length === 0) {
      return value;
    }
    if (parseInt(num_remaining) === -1) {
      $(count).text('0');
      $("#os-tour-notifications-menu-link").slideUp('slow');
      return;
    }
    if (parseInt(num_remaining) > -1) {
      $(count).text(num_remaining);
      if (!isNaN(parseFloat(value)) && isFinite(value)) {
        $(count).show();
        if (num_remaining > value) {
          $(count).text(value);
        }
      }
    }
  }

  /**
   * Sets the current user's "notifications_read" to the current time.
   *
   * Invoked when a user clicks "Done" on the final tour step.
   */
  function os_tour_notifications_read_update() {
    var settings = Drupal.settings.os_notifications;
    var url = '/os/tour/user/' + settings.uid + '/notifications_read';
    $.get(url, function(data) {
      console.log(data);
    });
  }

})(jQuery);

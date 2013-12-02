(function ($) {

  Drupal.behaviors.osEventsSideBySideEvents = {

    attach: function () {
      var eventsContainer = $(".calendar-agenda-items.single-day .calendar.item-wrapper .inner");

      // Loop over the containers of the events.
      eventsContainer.each(function () {

        $(this).each(function() {
          var eventsNumber = $(this).children().length;

          if (eventsNumber <= 1) {
            // No need for the side by side events when there is a single event.
            return;
          }

          var widthPerEvent = 100 / eventsNumber;

          $(this).children().each(function() {
            // Set a responsive width per event.
            var eventItem = $(this).find('.view-item-os_events');
            eventItem.css('width', widthPerEvent + '%');

            // Hiding the date of the event.
            var eventDescription = eventItem.find('.views-field-field-date').hide();

            // Attaching the date of the event to the title of the link.
            eventItem.find('.views-field-colorbox a').attr('title', $.trim(eventDescription.text()));
          });
        });
      });
    }
  };

})(jQuery);

/**
 * 
 */
(function ($) {
  var data = {};
  Drupal.behaviors.os_sv_list = {
    attach: function (ctx) {
    	
      // add a click handler
      $(ctx).find('.block-boxes-os_sv_list_box', ctx).click(click_handler).each(function () {
        // save the current page to our cache
        // get the delta of the box and the page, and store them that way
        var page_elem = $(this).find('[data-page]'),
          page = page_elem.attr('data-page'),
          delta = page_elem.attr('data-delta');
        
        data[delta] = {};
        data[delta][page] = page_elem.parent().html();
      });
      
      function click_handler(e) {
        // do nothing if this isn't a pager link
        if ($(e.target).parents('.pager').length == 0 || e.target.nodeName != 'A') return;
        e.stopPropagation();
        e.preventDefault();
        
        // get the requested page and delta from the query args
        var args = query_args(e.target.href),
            delta = args.sv_list_box_delta;
        
        // if there's no page set in the query, assume its the first page
        if (typeof args.page == 'undefined') {
          args.page = 0;
        }
        
        // get data from the cache
        if (typeof data[delta][args.page] != 'undefined') {
          var parent = $(e.currentTarget).find('.boxes-box-content').html(data[delta][args.page]);
          Drupal.attachBehaviors(parent);
        }
        // if it doesn't exist, we have to ask the server for it
        else {
          var s = Drupal.settings, 
            page = decodeURIComponent(args.page).split(',');
            page = page[args.pager_id];
          $.ajax({
            url: s.basePath + (typeof s.pathPrefix != 'undefined'?s.pathPrefix:'') + 'os_sv_list/page/'+delta,
            data: {
              page: page
            },
            beforeSend: function (xhr, settings) {
              $(e.currentTarget).append('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>')
            },
            success: function (commands, status, xhr) {
              var html, i,
              parent = $(e.currentTarget).find('.boxes-box-content');
              
              for (i in commands) {
                if (commands[i].command == 'insert' 
                  && commands[i].method == null 
                  && commands[i].selector == null 
                  && commands[i].data != "") {
                    html = commands[i].data;
                    break;
                }
              }
              // replace the existing page with the new one
              parent.html(html);
              Drupal.attachBehaviors(parent);
              // and add it to our cache so we won't have to request it again
              var page = parent.find('[data-page]').attr('data-page');
              data[delta][page] = html;
              $(e.currentTarget).find('.ajax-progress').remove();
            }
          });
        }
      }
    }
  };
  
  // splits the url into an object of its query arguments
  function query_args(url) {
    var frags = url.split('?'),
      args = {};
    frags = frags[1].split('&');
    for (var i=0; i<frags.length; i++) {
      var arg = frags[i].split('=');
      args[arg[0]] = arg[1];
    }
    
    return args;
  }
  
  function get_delta(elem) {
    return elem.id.replace('block-boxes-', '');
  }
})(jQuery);
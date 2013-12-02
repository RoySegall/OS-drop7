/**
 *  Javascript for the Control Panel menu.
 *  
 *   Does two things:
 *   1. Changes the menu select when the user drags a row
 *   2. Removes the 'hidden' class when the user selects a new menu from the select.
 */
(function($) {
var drag;

function changeSelect() {
  var $this = $(this.oldRowElement),
    $prev = $this.prevAll('.section-heading'),
    val = $prev.find('.menu-name').val(),
    select = $this.find('.menu-name');
  
  if (typeof this.rowObject.children != 'undefined') {
    $.each(this.rowObject.children, function () {
      $(this).find('.menu-name').val(val);
    });
  }
  
  select.val(val);
  emptySections();
}

function changeRegion() {
  // remove the hidden class
  var self = this;
  $('input').filter(function (i) {
     return (this.value && this.value == self.value);
  }).parents('tr').removeClass('hidden');
  
  // move the field to the new region
  var $row = $(self).parents('tr'),
      row = $row.get(0),
      $dest = $('tr.section-heading').filter(function() {
        return ($('.menu-name', this).val() == self.value);
      });
  $dest.after($row);
  
  // deal with tabledrag
  
  
  emptySections();
}

/** 
 * Deal with the empty section message.
 * If there no links in the section, switch to the region-empty class
 * Otherwise, switch to region-populated
 */
function emptySections() {
  var $table = $(drag.table),
  // get all the section messages
    $sections = $('.section-message');
  
  // loop through each select
  // find it's section header, then look down for the section message
  $('select.menu-name', $table).each(function () {
    var $header = $(this).parents('tr').prevAll('.section-heading').first(),
      $message = $header.nextAll('.section-message').first();
    
    // remove this message from the list we made earlier
    $sections = $sections.not($message);
    $message.removeClass('section-empty').addClass('section-populated');
  });
  
  // at this point, the $sections should only contain 
  // section messages in sections that are empty
  $sections.removeClass('section-populated').addClass('section-empty');
}
  
Drupal.behaviors.cp_menu_form = {
  attach: function (ctx) {
    // remove the 'hidden' class when a menu is changed
    $('select.menu-name', ctx).change(changeRegion);
    
    drag = Drupal.tableDrag['edit-menu-table'];
    drag.onDrop = changeSelect;
  }
};
})(jQuery);
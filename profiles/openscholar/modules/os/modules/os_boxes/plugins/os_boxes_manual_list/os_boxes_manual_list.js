/**
 * Allows users to add posts to their manual lists without an additional 
 * page load on top of the ajax call
 */
Drupal.behaviors.os_manual_list = {
	attach : function (ctx) {
		var $ = jQuery;
		if ($('#manual-nodes-list', ctx).length == 0) return;	// do nothing if our table doesn't exist
		
		var $form = $('#boxes-add-form, #boxes-box-form'),
			template = '<tr class="draggable">'+$('input[name="nodes[blank][nid]"]', $form).parents('tr').hide().html()+'</tr>',
			tableDrag = Drupal.tableDrag['manual-nodes-list'],
			new_id = parseInt($('#edit-count').val());
		
		// add a new row to the table, set all its form elements to the right values and make it draggable
		$('.add_new', $form).click(function (e) {
			var val = $('#edit-node-to-add', $form).val(),
				patt = /(.+) \[([\d]+)\]/,
				matches = patt.exec(val),
				id, weight = -Infinity,
				new_row;
			
			// there should actually be something in the field
			if (matches != null) {
				var count = $('#edit-count'),
					title = matches[1],
					nid = matches[2];
				count.val(parseInt(count.val())+1);
				id = new_id++;
				new_row = $(template.replace(/blank/g, id));
				
				// get the new weight
				$('.field-weight', $form).each(function () {
					if ($(this).val() > weight) {
						weight = parseInt($(this).val());
					}
				});
				// there are no existing form elements, start at 0.
				if (weight == -Infinity) {
					weight = 0;
				}
				
				// set all the form elements in the new row
				$('input[name="nodes['+id+'][nid]"]', new_row).val(nid);
				$('span', new_row).text(matches[1]);
				$('input[name="nodes['+id+'][title]"]', new_row).val(title);
				$('input[name="nodes['+id+'][weight]"]', new_row).addClass('field-weight').val(weight+1);
				$('input[name="nodes['+id+'][weight]"]', new_row).parents('td').css('display', 'none');
				//$('.tabledrag-handle', new_row).remove();
				$('table tbody', $form).append(new_row);
				new_row = $('input[name="nodes['+id+'][nid]"]', $form).parents('tr');
				$('#edit-node-to-add', $form).val('');
				
				setup_remove(new_row);
	
				tableDrag.makeDraggable(new_row[0]);
			}
		});
		
		// set up remove links.
		function setup_remove(ctx) {
			$('.remove', ctx).click(function () {
				var $this = $(this);
				$this.parents('tr').remove();
				
				// decrement counter
				var count = $('#edit-count');
				count.val(parseInt(count.val())-1);
				
				return false;
			});
		}
		
		setup_remove($form);
	}
};
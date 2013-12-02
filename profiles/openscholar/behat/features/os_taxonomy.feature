Feature:
  Testing the term tagged items pager.

  @api
  Scenario: Testing the term tagged items pager.
     Given I am logging in as "john"
      When I assign the node "John F. Kennedy" to the term "Stephen William Hawking"
       And I assign the node "I opened a new personal" with the type "news" to the term "Stephen William Hawking"
       And I assign the node "First blog" with the type "blog" to the term "Stephen William Hawking"
       And I assign the node "John doe biography" with the type "bio" to the term "Stephen William Hawking"
       And I assign the node "John doe\'s curriculum" with the type "cv" to the term "Stephen William Hawking"
       And I assign the node "I opened a new personal" with the type "news" to the term "Stephen William Hawking"
       And I set the variable "os_taxonomy_items_per_page" to "3"
       And I visit "john/authors/stephen-william-hawking"
      Then I should see a pager

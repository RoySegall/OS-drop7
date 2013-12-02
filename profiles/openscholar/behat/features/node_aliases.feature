Feature:
  Testing the aliases of a node.

  @api
  Scenario: Check that the OG audience field will be shown when editing content.
    Given I am logging in as "john"
      And I visit "node/add/blog"
      And I fill in "Title" with "Unique Title"
      And I press "edit-submit"
      And I edit the node "Unique Title"
     Then I verify the "URL alias" value is "blog/unique-title"

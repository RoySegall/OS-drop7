Feature:
  Test the redirect of the "cancel" button on node forms.

  @api
  Scenario: Test redirect when user edits a node (no destination).
    Given I am logging in as "john"
      And I visit "john"
      And I edit the node "first blog"
      And I click "Cancel"
     Then I should be on "john/blog"

  @api
  Scenario: Test redirect when user edits a node using the contextual link (with destination).
    Given I am logging in as "john"
      And I visit "john/blog"
      And I edit the node of type "blog" named "first blog" using contextual link
      And I click "Cancel"
     Then I should be on "john/blog"

  @api
  Scenario: Test redirect when user creates a page.
    Given I am logging in as "john"
      And I visit "john"
      And I visit "john/node/add/page"
      And I click "Cancel"
     Then I should be on "john"

Feature:
  Testing the comment publishing for a blog entry.

  @api
  Scenario: Check that a user can create a new blog post
    Given I am logging in as "john"
     When I visit "john/blog"
      And I click "First blog"
      And I add a comment "Lorem ipsum john doe" using the comment form
     Then I should see "Lorem ipsum john doe"

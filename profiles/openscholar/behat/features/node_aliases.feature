Feature:
  Testing the aliases of a node.

  @api
  Scenario: Verify that the pathauto alias is properly created in nodes.
    Given I am logging in as "john"
      And I visit "john/node/add/blog"
      And I fill in "Title" with "Unique Title"
     When I press "edit-submit"
     Then I verify the alias of node "Unique Title" is "john/blog/unique-title"

  @api
  Scenario: Verify that the custom alias is properly created in nodes.
    Given I am logging in as "john"
      And I visit "john/node/add/blog"
      And I fill in "Title" with "Another Unique Title"
      And I uncheck the box "Generate automatic URL alias"
      And I fill in "edit-path-alias" with "unique-custom-alias"
     When I press "edit-submit"
     Then I verify the alias of node "Another Unique Title" is "john/unique-custom-alias"

  @api
  Scenario: Verify that aliases are displayed without purl in node edit form.
    Given I am logging in as "john"
     When I edit the node "Unique Title"
     Then I verify the "URL alias" value is "blog/unique-title"

  @api @wip
  Scenario: Verify it is possible to use the purl as a node custom path.
    Given I am logging in as "john"
      And I visit "john/node/add/blog"
      And I fill in "Title" with "John Custom Alias"
      And I uncheck the box "Generate automatic URL alias"
      And I fill in "edit-path-alias" with "john"
     When I press "edit-submit"
     Then I verify the alias of node "John Custom Alias" is "john/john"

  @api
  Scenario: Verify it is impossible to use a duplicate purl in node custom path.
    Given I am logging in as "john"
      And I visit "john/node/add/blog"
      And I fill in "Title" with "John Second Custom Alias"
      And I uncheck the box "Generate automatic URL alias"
      And I fill in "edit-path-alias" with "john/john/john/jfk-duplicate-purl"
     When I press "edit-submit"
     Then I verify the alias of node "John Second Custom Alias" is "john/jfk-duplicate-purl"

  @api
  Scenario: Testing shared domain with two different vsite and the same node
  title are working properly.
    Given I am logging in as "admin"
      And I define "john" domain to "lincoln.local"
      And I define "lincoln" domain to "lincoln.local"
      And I visit "http://lincoln.local/john/about"
      And I should see "Page about john"
      And I verify the url is "lincoln.local"
     When I visit "http://lincoln.local/lincoln/about"
     Then I should see "Page about lincoln"
      And I verify the url is "lincoln.local"

  @api
  Scenario: Verify it is impossible to use aliases if they exist without the
            purl.
    Given I am logging in as "john"
      And I visit "john/node/add/blog"
      And I fill in "Title" with "This Node Should Not Exist"
      And I uncheck the box "Generate automatic URL alias"
      And I fill in "edit-path-alias" with "user"
      And I press "edit-submit"
      And I should see "The alias is already in use."
     When I fill in "edit-path-alias" with "blog"
      And I press "edit-submit"
     Then I should see "The alias is already in use."

  @api
  Scenario: Verify the user can enter an alias with node type at the start.
            i.e: when user create a new presentation he can can set the alias as
            presentation/new-presentation.
    Given I am logging in as "john"
      And I visit "john/node/add/presentation"
      And I fill in "Title" with "Checking a presentation"
      And I uncheck the box "Generate automatic URL alias"
      And I fill in "edit-path-alias" with "presentations/checking-presentation"
     When I press "Save"
     Then I should see "Presentation Checking a presentation has been created."

  @api
  Scenario: Verify the user can't enter an alias with a menu item which already
            in use.
            i.e: Verify user can't create post with the alias 'user/login'.
    Given I am logging in as "john"
      And I visit "john/node/add/presentation"
      And I fill in "Title" with "Checking a presentation"
      And I uncheck the box "Generate automatic URL alias"
      And I fill in "edit-path-alias" with "user/login"
     When I press "Save"
     Then I should see "The alias is already in use."


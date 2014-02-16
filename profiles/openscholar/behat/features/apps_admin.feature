Feature:
  Testing the managing of OpenScholar

  @api
  Scenario: Check that all of the apps are turned on
    Given I am logging in as "john"
      And I visit "john"
     When I click "Build"
      #And I should see "Apps"
     Then I should see the "spaces" table with the following <contents>:
      | Bio/CV        | Public |
      | Blog          | Public |
      | Booklets      | Public |
      | Classes       | Public |
      | Dataverse     | Public |
      | Events        | Public |
      | Image Gallery | Public |
      | Links         | Public |
      | News          | Public |
      | Basic Pages   | Public |
      | Presentations | Public |
      | Profiles      | Public |
      | Publications  | Public |
      | Reader        | Public |
      | Software      | Public |

    @api
    Scenario: Check site owner can't manage permissions of disabled app.
      Given I am logging in as "john"
        And I set feature "edit-spaces-features-os-booklets" to "Disabled" on "john"
       When I visit "john/cp/users/permissions"
       Then I should not see "Create book page content"
        And I should see "Create Bio content"

    @api
    Scenario: Check enabling app brings back its permissions.
      Given I am logging in as "john"
        And I set feature "edit-spaces-features-os-booklets" to "Public" on "john"
       When I visit "john/cp/users/permissions"
       Then I should see "Create book page content"

    @api
    Scenario: Check content editor can edit widgets by default
      Given I am logging in as "john"
       When I give the user "klark" the role "content editor" in the group "john"
        And I click "Log out"
        And I am logging in as "klark"
        And I go to "john/os/widget/boxes/os_addthis/edit"
       Then I should get a "200" HTTP response

    @api
    Scenario: Check content editor without edit boxes permission can't edit
      Given I am logging in as "john"
       When I give the user "klark" the role "content editor" in the group "john"
        And I go to "john/cp/users/permissions"
       When I click "Edit roles and permissions"
        And I press "Confirm"
        And I go to "john/cp/users/permissions"
       Then I should see the button "Save permissions"
        And I remove the role "content editor" in the group "john" the permission "Edit boxes"
        And I click "Log out"
        And I am logging in as "klark"
        And I go to "john/os/widget/boxes/os_addthis/edit"
       Then I should get a "403" HTTP response

    @api
    Scenario: Check rolling abck permissions re-enable widget permissions
      Given I am logging in as "john"
       When I give the user "klark" the role "content editor" in the group "john"
        And I go to "john/cp/users/permissions"
       When I click "Restore default roles and permissions"
        And I press "Confirm"
        And I click "Log out"
        And I am logging in as "klark"
        And I go to "john/os/widget/boxes/os_addthis/edit"
       Then I should get a "200" HTTP response

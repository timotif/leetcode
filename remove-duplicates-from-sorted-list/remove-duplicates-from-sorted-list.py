# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = head
        while (cur):
            next = cur.next
            while next and cur.val == next.val:
                next = next.next
            cur.next = next
            cur = next
        return head
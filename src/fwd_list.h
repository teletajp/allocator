#pragma once
#include <memory>
#include <iostream>
template <class T, class Alloc = std::allocator<T>>
class fwd_list
{
public:
    using value_type = T;
    using allocator_type = Alloc;
    using alloc_traits = std::allocator_traits<allocator_type>;
    using pointer = typename alloc_traits::pointer;
    using const_pointer = typename alloc_traits::const_pointer;
    using size_type = typename alloc_traits::size_type;
    using difference_type = typename alloc_traits::difference_type;
    using reference = value_type &;
    using const_reference = const value_type &;
private:
	struct node_type
    {
		T value_;
        node_type *next_;
		node_type():value_{T()}, next_{nullptr}{}
		node_type(T value):value_(value), next_(nullptr){}
		node_type(T &&value):value_(std::move(value)), next_(nullptr){}
		node_type(const node_type & rhs):value_(rhs.value), next_(rhs.next_){}
        const bool operator==(const node_type & rhs) const {return (value_==rhs.value_ && next_ == rhs.next_);};
	};

	node_type *head_ = nullptr;
	node_type **ptail_ = nullptr;
    using allocator_t = typename alloc_traits:: template rebind_alloc<node_type>;
    allocator_t allocator_;
public:
    fwd_list():head_(nullptr), ptail_(&head_){};
    ~fwd_list()
    {
        auto node = head_;
        while (node)
        {
            auto cur_node = node;
            node = cur_node->next_;
            allocator_.destroy(cur_node);
            allocator_.deallocate(cur_node, 1);
        }
    }
    //void push_back(T&& value)
    //{
    //    try
    //    {
    //        auto & tail = *ptail_;
    //        tail = allocator_.allocate(1);
    //        allocator_.construct(tail, std::move(T(value)));
    //        ptail_ = &tail->next_;
    //    }
    //    catch(std::bad_alloc ex) {throw ex;}
    //    catch(std::invalid_argument ex) {throw ex;}  
    //}
    void push_back(T value)
    {
        try
        {
            auto & tail = *ptail_;
            tail = allocator_.allocate(1);
            allocator_.construct(tail, T(value));
            ptail_ = &tail->next_;
        }
        catch (std::bad_alloc ex) { throw ex; }
        catch (std::invalid_argument ex) { throw ex; }
    }
    bool empty() const {return head_ == nullptr;};

    class fwd_list_iter
    {
        private:
            node_type *node_;
        public:
            fwd_list_iter():node_(nullptr){}
            fwd_list_iter(node_type *node):node_(node){}
            fwd_list_iter(const fwd_list_iter& rhs):node_(rhs.node_){}
            const fwd_list_iter& operator=(const fwd_list_iter& rhs) {node_ = rhs.node_; return *this;}
            ~fwd_list_iter() = default;

            reference operator*() { if(node_ == nullptr) throw; return node_->value_;}
            pointer operator->() { if(node_ == nullptr) throw; return &(node_->value_);}
            const bool operator!=(const fwd_list_iter& rhs)const{return !(node_ == rhs.node_);}
            fwd_list_iter& operator++(){ node_ = node_->next_; return *this;};
    };
    using iterator = fwd_list_iter;

    iterator begin(){return iterator(head_);}
    iterator end(){return iterator(*ptail_);}
};